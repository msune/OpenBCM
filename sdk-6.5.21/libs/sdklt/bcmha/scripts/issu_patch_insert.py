#
# \file patch_insert.py
#
# Introduce new patches to the system.
#
# This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
# 
# Copyright 2007-2020 Broadcom Inc. All rights reserved.
#
import sys
import subprocess
import os
import os.path
import csv
import tempfile
import filecmp
import shutil
import getopt
import yaml  # YAML parser
from collections import OrderedDict  # keep YAML parser output in order
import issu_version_list

ISSU_DB_DIR = '/bcmissu/dll/db'
ISSU_DLL_MAIN_DIR = '/bcmissu/dll/main'
ISSU_PATCH_DBFILE = 'patches.db'
ISSU_PATCH_CFILE = 'issu_patches.c'
ISSU_PATCH_BUILD_EXT = 'comp_patch.mk'


# Defines structure DB entry.
class patch_db_entry:
    component = ''  # Component associated with the patch.
    handler = ''  # Patch handler.
    version = ''  # Version that the patch was introduced
    device = ''  # Device associated with this patch
    variant = ''  # Variant information that this patch related to
    priority = 0  # Patch priority, larger number has lower priority.
    included = False  # Indicate if the entry was already processed


# This class deals with ISSU h/w patches. It can add a single patch to the
# patch list of a particular version. It can also accumulate all the patches
# from several versions and create a C file to point to the patches handlers.
class issu_patch:
    """Global class to handle patches."""

    def __init__(self, issu_db_dir, start_ver, target_ver):
        self.patch_id_dict = {}  # The local patch dictionary keyed by patch ID.
        self.issu_db_dir = issu_db_dir
        self.issu_dll_main_dir = issu_db_dir + '../main'
        self.file_name = issu_db_dir + '/../' + ISSU_PATCH_DBFILE
        self.versions = []
        self.start_ver = start_ver
        self.target_ver = target_ver

    # This method set the class to look at a particular version.
    def set_version(self, version, device, variant):
        self.version = version
        self.device = device
        self.variant = variant

    # This function determine if a given version is in the range of
    # start_ver : target_ver
    def __in_range(self, ver):
        ver_c = issu_version_list.issu_version_list(None,
                                                    self.start_ver,
                                                    self.target_ver)
        return ver_c.ver_in_range(ver)

    # This method reads the patches for the set version into the local
    # patch dictionary.
    def read_patch_db(self, version_filter = []):
        try:
            fh = open(self.file_name, 'r')
        except:
            return

        self.versions = version_filter  # Save the sorted version list

        # Read the content of the file into csv dictionary
        csvdict = csv.DictReader(fh, fieldnames = ['id', 'component', \
                                                   'handler', 'version', \
                                                   'device', 'variant', \
                                                   'priority'])

        dict = self.patch_id_dict
        # Populate the structure dictionary with the content found in
        # ISSU_PATCH_DBFILE
        for rec in csvdict:
            if len(version_filter) > 0 and not self.__in_range(rec['version']):
                continue
            ent = patch_db_entry()
            ent.component = rec['component']
            ent.handler = rec['handler']
            ent.version = rec['version']
            ent.device = rec['device']
            ent.variant = rec['variant']
            ent.priority = int(rec['priority'])
            dict[rec['id']] = ent

        fh.close()

    # This method writes the content of the patch dictionary into a patch DB
    # within the current version.
    def write_patch_db(self):
        try:
            fh = open(self.file_name, 'w')
        except:
            print ('Failed to open file ', self.file_name)
            return -1

        for id in sorted(self.patch_id_dict.keys()):
            ent = self.patch_id_dict[id]
            fh.write('%s,%s,%s,%s,%s,%s,%d\n' %
                     (id, ent.component, ent.handler,
                      ent.version, ent.device, ent.variant, ent.priority))

        fh.close()
        return 0

    # This method inserts a patch information into the local patch dictionary.
    def patch_insert(self, id, component, handler, priority):
        if id in self.patch_id_dict.keys():
            print ('Patch already exist')
            return -1
        ent = patch_db_entry()
        ent.component = component
        ent.handler = handler
        ent.priority = priority
        ent.version = self.version
        ent.device = self.device
        ent.variant = self.variant
        self.patch_id_dict[id] = ent
        return 0

    # This method writes the standard header of a generated C file.
    def prepare_generic_output_file_header(self, fh):
        fh.write('/*************************************************************************\n')
        fh.write(' *\n')
        fh.write(' * DO NOT EDIT THIS FILE!\n')
        fh.write(' * This file is auto-generated by HA parser from YAML formated file.\n')
        fh.write(' * Edits to this file will be lost when it is regenerated.\n')
        fh.write(' * Tool: $SDK/bcmha/scripts/issu_patch_insert.py\n')
        fh.write(' *\n')
        fh.write(' * $Copyright:.$\n')
        fh.write(' *\n')
        fh.write(' *************************************************************************/\n')
        fh.write('\n')
        fh.write('#include <bcmissu/issu_types.h>\n')

    # This method generate a C file that contains the content of all the patches within
    # the local patch dictionary.
    def create_patch_c_file(self):
        out_file = self.issu_db_dir + '/base/' + ISSU_PATCH_CFILE
        try:
            fh = open(out_file, 'w')
        except:
            print ('failed to open file ', out_file)
            return -1

        self.prepare_generic_output_file_header(fh)

        fh.write('\n')
        # Define all the external functions that will be used
        for id in self.patch_id_dict.keys():
            ent = self.patch_id_dict[id]
            fh.write('extern int %s_%s(int unit);\n' % (ent.component, ent.handler))

        # The patch list will be sorted based on priority where higher priority patches
        # will be in lower index of the array.
        fh.write('static const bcmissu_comp_patch_hdl_t patch_list[] = {\n')
        for i in range(0, len(self.versions)):
            for id in sorted(self.patch_id_dict, key = lambda x: self.patch_id_dict[x].priority):
                ent = self.patch_id_dict[id]
                if not self.patch_id_dict[id].included:
                    self.patch_id_dict[id].included = True
                    fh.write('    { %s, \"%s\", \"%s\", \"%s\", %s_%s },\n' %
                             (id, ent.version, ent.device, ent.variant, ent.component, ent.handler))

        fh.write('    { 0, NULL, NULL }\n')
        fh.write('};\n')

        # Declare the public function that can retrieve the patch list.
        fh.write('\nconst bcmissu_comp_patch_hdl_t *bcmissu_patch_list_get(void)\n')
        fh.write('{\n')
        fh.write('    return patch_list;\n')
        fh.write('}\n')

        # Close the file
        fh.close()
        return 0

    # The components containing the patch should be added to the build system
    # This function creates the 'comp_patch.ext' file that will be included
    # within the DLL makefile
    def create_patch_makefile(self):
        out_dir = self.issu_dll_main_dir + '/generated'
        if not os.path.isdir(out_dir):
            try:
                os.makedirs(out_dir)
            except OSError:
                print('Failed to create target directory %s\n' % out_dir)
                return -1
        out_file = out_dir + '/' + ISSU_PATCH_BUILD_EXT
        try:
            fh = open(out_file, 'w')
        except:
            print ('failed to open file ', out_file)
            return -1

        # Write the file header
        fh.write('#\n')
        fh.write('# $Copyright: Broadcom Ltd.$\n')
        fh.write('#\n')
        fh.write('# Component patches makefile extensions.\n')
        fh.write('# This is auto generated file.\n')
        fh.write('# Edits to this file will be lost when it is regenerated.\n')
        fh.write('# Tool: $SDK/bcmha/scripts/issu_patch_insert.py\n\n')

        if (len(self.patch_id_dict) == 0):
            return 0

        comp_list = []
        # Define the source directories
        for id in self.patch_id_dict.keys():
            ent = self.patch_id_dict[id]
            if not ent.component in comp_list:
                comp_list.append(ent.component)
                fh.write('%s_COMP_PATCH_SRC = $(SDK)/%s/issu_dll\n' %
                         (ent.component.upper(), ent.component))

        # Update the VPATH
        fh.write('\nVPATH += ')
        comp_list = []
        for id in self.patch_id_dict.keys():
            ent = self.patch_id_dict[id]
            if not ent.component in comp_list:
                comp_list.append(ent.component)
                fh.write('\\\n    $(%s_COMP_PATCH_SRC) ' % ent.component.upper())

        # Update the list of C source files
        fh.write('\n\n')
        comp_list = []
        for id in self.patch_id_dict.keys():
            ent = self.patch_id_dict[id]
            if not ent.component in comp_list:
                comp_list.append(ent.component)
                fh.write('COMP_VSRCS += $(wildcard $(%s_COMP_PATCH_SRC)/*.c)\n' %
                         (ent.component.upper()))

        fh.write('\nCOMP_LSRCS = $(notdir $(COMP_VSRCS))\n')
        fh.write('COMP_LOBJS = $(addsuffix .o, $(basename $(COMP_LSRCS)))\n')
        fh.write('BOBJS += $(addprefix $(BLDDIR)/,$(COMP_LOBJS))\n')
        fh.write('VSRCS += $(COMP_VSRCS)\n')

        # Update the include path
        comp_list = []
        fh.write('\nSDK_CPPFLAGS += ')
        for id in self.patch_id_dict.keys():
            ent = self.patch_id_dict[id]
            if not ent.component in comp_list:
                comp_list.append(ent.component)
                fh.write('\\\n    -I$(SDK)/%s/include' % ent.component)

        fh.write('\n')
        # Close the file
        fh.close()
        return 0


def usage():
    print ('python patch_insert.py -v <version> -i <patch_id> -c <component> -l <handler>' \
           ' [-p priority] [-d <device>] [-t <variant>] | -h')
    print ('Where <version> is the version that this patch will be introduced')
    print ('      <patch_id> is the hexadecimal id of the patch (see patch_id_gen.sh)')
    print ('      <component> is the component that owns the patch')
    print ('      <handler> is the handler that handles the patch.\n')
    print ('      <priority> is the precedence of this patch with respect to others. 0 is highest (default).')
    print ('      <device> is the device name such as bcm56990_a0')
    print ('      <variant> is the variant that this patch associated with. Skip if the device has no variants.')


# The main function.
# Add a patch into the patch YAML file
def main(argv):
    version = None
    device = '*'
    variant = '*'
    component = None
    handler = None
    patch_id = None
    priority = 0

    try:
        sdk = os.environ['SDK']
    except:
        print('environment variable SDK required')
        sys.exit(-1)

    # Check if there are any input parameters
    try:
        opts, args = getopt.getopt(argv, "hv:t:i:c:l:p:d:", ["help"])
    except getopt.GetoptError:
        usage()
        sys.exit(-1)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit(0);
        elif opt == '-v':
            version = arg
        elif opt == '-t':
            variant = arg.lower()
        elif opt == '-d':
            device = arg
        elif opt == '-i':
            patch_id = arg
        elif opt == '-c':
            component = arg
        elif opt == '-l':
            handler = arg
        elif opt == '-p':
            priority = int(arg)
        else:
            usage()
            sys.exit(-1)

    # Verify that all the inputs are available
    if (not version or not component or not handler or not patch_id):
        usage()
        sys.exit(-1)

    patch_cls = issu_patch(sdk + ISSU_DB_DIR, None, None)
    patch_cls.set_version(version, device, variant)
    patch_cls.read_patch_db()
    if (patch_cls.patch_insert(patch_id, component, handler, priority) != 0) or \
        (patch_cls.write_patch_db() != 0):
        print ('Failed to insert patch')
        sys.exit(-1)


if __name__ == "__main__":
    if sys.version_info[0] < 2 or \
       (sys.version_info[0] == 2 and sys.version_info[1] < 7):
        print('Error: Unsupported python version, min version 2.7.x')
    else:
        main(sys.argv[1:])
