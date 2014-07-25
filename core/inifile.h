/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.0x                         */
/*             Copyright (C)1998-2014, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
#ifndef __INCLUDED_INIFILE_H__
#define __INCLUDED_INIFILE_H__

#include <string>

std::string FilePath(const std::string directoryName, const std::string fileName);

class WIniFile {
 private:
  struct ini_info_type {
    int nIndex;
    char *pIniSectionBuffer;
    char **pKeyArray;
    char **pValueArray;
  };

 public:
  WIniFile(const std::string filename, const std::string primarySection, const std::string secondarySection = "");
  // Constructor/Destructor
  virtual ~WIniFile(); 

  // Member functions
  bool Open(const std::string primarySection, const std::string secondarySection);
  bool Close();
  bool IsOpen() const { return open_; }

  const char* GetValue(const char *pszKey, const char *pszDefaultValue = NULL);
  const long GetNumericValue(const char *pszKey, int nDefaultValue = 0);
  const bool GetBooleanValue(const char *pszKey, bool defaultValue = false);

 private:
  /**
   * Reads a specified value from INI file data (contained in *inidata). The
   * name of the value to read is contained in *value_name. If such a name
   * doesn't exist in this INI file subsection, then *val is NULL, else *val
   * will be set to the string value of that value name. If *val has been set
   * to something, then this function returns 1, else it returns 0.
   */
  static bool StringToBoolean(const char *p);

  /**
   * Allocates memory and returns pointer to location containing requested data within a file.
   */
  char *ReadSectionIntoMemory(long begin, long end);

  /**
   * Returns begin and end locations for specified subsection within an INI file.
   * If subsection not found then *begin and *end are both set to -1L.
   */
  void FindSubsectionArea(const std::string& section, long *begin, long *end);

  /**
   * Reads a subsection from specified .INI file, the subsection being specified
   * by *pszHeader. Returns a ptr to the subsection data if found and memory is
   * available, else returns NULL.
   */
  char *ReadFile(const std::string header);

  void Parse(char *pBuffer, ini_info_type * info);

  const std::string file_name_;
  bool open_;
  ini_info_type m_primarySection;
  ini_info_type m_secondarySection;
};

#endif  // __INCLUDED_INIFILE_H__
