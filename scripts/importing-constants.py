import os
import re

# ask the user for keyword, use raw_input() on Python 2.x
keyword = input("Unit::")
regex = "(.*Unit )(.*Unit)::(.*)\(\"(.*)\"\)"
# path to the root directory to search
root_dir = "/opt/biogears/core/projects/biogears/libBiogears/src/cdm/properties"
for root, dirs, files in os.walk(root_dir, onerror=None):  # walk the root dir
    for filename in files:  # iterate over the files in the current dir
        file_path = os.path.join(root, filename)  # build the file path
        try:
            with open(file_path, "rb") as f:  # open the file for reading
                dummystring = ""
                dummyfilename=""

                # read the file line by line
                for line in f:  # use: for i, line in enumerate(f) if you need line numbers
                    try:
                        line = line.decode("utf-8")  # try to decode the contents to utf-8
                    except ValueError:  # decoding failed, skip the line
                        continue
                    x = re.search(regex,line)
                    if x:
                        filenametoprint = f"#include <biogears/cdm/properties/{os.path.splitext(filename)[0]+'.h'}>"
                        # if dummyfilename!=filenametoprint:
                        #     print(filenametoprint)
                        # dummyfilename=filenametoprint

                        classstring=f"py::class_<biogears::{x[2]}>(m, \"{x[2]}\")"
                        if dummystring!=classstring:
                            print(";")
                            print(classstring)
                        dummystring = classstring
                        # str = "\"" + x[2]+"::"+x[3]+"\""
                        staticstring = f".def_readonly_static(\"{x[3]}\",&biogears::{x[2]}::{x[3]})"
                        # str2 = "\""+x[4]+"\","
                        # print(str+":"+str2+str3)
                        print(staticstring)
                    # if keyword in line:  # if the keyword exists on the current line...
                    #     print(file_path)  # print the file path
                    #     print(line)
                    #     break  # no need to iterate over the rest of the file
        except (IOError, OSError):  # ignore read and permission errors
            pass
