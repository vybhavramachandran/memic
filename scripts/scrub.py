import re

f = open("regex-physiology.xml", "r")
# print(f.read())
complex_category_regex = re.compile("<xs:complexType name=\"(.*)\">")
complex_category_end_regex = re.compile("</xs:complexType>")

simple_category_regex = re.compile("<xs:simpleType name=\"(.*)\">")
simple_category_end_regex = re.compile("</xs:simpleType>")

variable_regex = re.compile("<xs:element name=\"(.*)\" type=\"(.*)\" minOccurs")
category = ""
final_dict = {}
dummy_dict={}
for line in f:
    if complex_category_regex.search(line)!=None :
        # print(complex_category_regex.findall(line)[0])
        category = complex_category_regex.findall(line)[0]
    elif simple_category_regex.search(line)!=None:
        category = simple_category_regex.findall(line)[0]
    elif complex_category_end_regex.search(line)!=None or simple_category_end_regex.search(line)!=None:
        if dummy_dict!={}:
            final_dict[category]=dummy_dict
        # print(dummy_dict)
        category=""
        dummy_dict={}
    else:
        result = variable_regex.findall(line)
        if result:
            dummy_dict[result[0][0]]=result[0][1]
            # print(f""+category+":"+result[0][0]+":"+result[0][1])
            # print(result[0][1])
        else:
            pass
print(final_dict)
