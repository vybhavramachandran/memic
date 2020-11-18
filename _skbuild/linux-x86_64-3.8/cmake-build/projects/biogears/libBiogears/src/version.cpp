#include <biogears/version.h>

#include <biogears/string/manipulation.h>

#include <cstdlib>
#include <cstring>
#include <cmath>

namespace biogears {


//-----------------------------------------------------------------------------

constexpr char const * _PROJECT_NAME_ = "Biogears";
constexpr char const * _REV_HASH_ = "23e396d1";
constexpr char const * _REV_TAG_ = "7.3.1";
constexpr char const * _REV_COMMIT_DATE_= "2020-11-09 12:12:37 +0530";
constexpr bool _OFFICAL_RELEASE_ = false;

constexpr int _MAJOR_VERSION_NUMBER_  = 7;
constexpr int _MINOR_VERSION_NUMBER_  = 3;
constexpr int _PATCH_VERSION_NUMBER_  = 1;
constexpr char const * _TWEAK_VERSION_NUMBER_  = "148";


using namespace std::string_literals;
//-----------------------------------------------------------------------------
std::string rev_commit_date() {
  return biogears_build_date_str();
}
//-----------------------------------------------------------------------------
const char * rev_commit_date_str() {
  return _REV_COMMIT_DATE_;
}
//-----------------------------------------------------------------------------
std::string biogears_build_date() {
  return biogears_build_date_str();
}
//-----------------------------------------------------------------------------
const char * biogears_build_date_str() {
  return __DATE__;
}
//-----------------------------------------------------------------------------
std::string version_string()
{
  if ( 0 == std::strlen(_TWEAK_VERSION_NUMBER_)) {
    return biogears::asprintf("%d.%d.%d" ,_MAJOR_VERSION_NUMBER_,_MINOR_VERSION_NUMBER_,_PATCH_VERSION_NUMBER_);
  } else {
    return biogears::asprintf("%d.%d.%d+%s", _MAJOR_VERSION_NUMBER_,_MINOR_VERSION_NUMBER_,_PATCH_VERSION_NUMBER_,_TWEAK_VERSION_NUMBER_);
  }
}
//-----------------------------------------------------------------------------
char const * version_string_str()
{
  static std::string version_str; 
  if( version_str.empty() )
  {  version_str = version_string(); }
  return version_str.c_str();
}
//-----------------------------------------------------------------------------
std::string full_version_string()
{
  if ( 0 == std::strlen(_TWEAK_VERSION_NUMBER_)) {
    return biogears::asprintf("%d.%d.%d-%s", _MAJOR_VERSION_NUMBER_,_MINOR_VERSION_NUMBER_,_PATCH_VERSION_NUMBER_,_REV_HASH_);
  } else {
    return biogears::asprintf("%d.%d.%d+%s-%s", _MAJOR_VERSION_NUMBER_,_MINOR_VERSION_NUMBER_,_PATCH_VERSION_NUMBER_,_TWEAK_VERSION_NUMBER_,_REV_HASH_);
  }
}
//-----------------------------------------------------------------------------
char const * full_version_string_str()
{
  static std::string full_version_str; 
  if( full_version_str.empty() )
  {  full_version_str = full_version_string(); }
  return full_version_str.c_str();

}
//-----------------------------------------------------------------------------
std::string project_name()
{
  return _PROJECT_NAME_;
}
//-----------------------------------------------------------------------------
char const * project_name_str()
{
 return _PROJECT_NAME_;
}
//-----------------------------------------------------------------------------
std::string rev_hash()
{
  return _REV_HASH_;
}
//-----------------------------------------------------------------------------
char const * rev_hash_str()
{
  return _REV_HASH_;
}
//-----------------------------------------------------------------------------
std::string rev_tag()
{
  return _REV_TAG_; 
}

//-----------------------------------------------------------------------------
char const * rev_tag_str()
{
  return _REV_TAG_;
}
//-----------------------------------------------------------------------------

int rev_offset()
{
  auto offset = std::strtol(_TWEAK_VERSION_NUMBER_, nullptr, 10);
  if(errno == ERANGE)
  { 
    return -1;
  } else {
    return offset;
  }
}
//-----------------------------------------------------------------------------

int biogears_major_version()
{
  return _MAJOR_VERSION_NUMBER_;
}
//-----------------------------------------------------------------------------
int biogears_minor_version()
{
  return _MINOR_VERSION_NUMBER_;
}
//-----------------------------------------------------------------------------
int biogears_patch_version()
{
  return _PATCH_VERSION_NUMBER_;
}
//-----------------------------------------------------------------------------
bool biogears_offical_release()
{
  return _OFFICAL_RELEASE_;
}
}
