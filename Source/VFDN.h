/* ------------------------------------------------------------
name: "VFDN"
Code generated with Faust 2.59.5 (https://faust.grame.fr)
Compilation options: -a faustMinimal.h -lang cpp -i -inpl -ct 1 -cn VFDN -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __VFDN_H__
#define  __VFDN_H__

#include <cmath>
#include <cstring>

/************************** BEGIN MapUI.h ******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __UI_H__
#define __UI_H__

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***************************************************************************/

#ifndef __export__
#define __export__

// Version as a global string
#define FAUSTVERSION "2.59.5"

// Version as separated [major,minor,patch] values
#define FAUSTMAJORVERSION 2
#define FAUSTMINORVERSION 59
#define FAUSTPATCHVERSION 5

// Use FAUST_API for code that is part of the external API but is also compiled in faust and libfaust
// Use LIBFAUST_API for code that is compiled in faust and libfaust

#ifdef _WIN32
    #pragma warning (disable: 4251)
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #elif FAUST_LIB
        #define FAUST_API __declspec(dllexport)
        #define LIBFAUST_API __declspec(dllexport)
    #else
        #define FAUST_API
        #define LIBFAUST_API 
    #endif
#else
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #else
        #define FAUST_API __attribute__((visibility("default")))
        #define LIBFAUST_API __attribute__((visibility("default")))
    #endif
#endif

#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct FAUST_API UIReal {
    
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* /*zone*/, const char* /*key*/, const char* /*val*/) {}

    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct FAUST_API UI : public UIReal<FAUSTFLOAT> {
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __PathBuilder__
#define __PathBuilder__

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <regex>


/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class FAUST_API PathBuilder {

    protected:
    
        std::vector<std::string> fControlsLevel;
        std::vector<std::string> fFullPaths;
        std::map<std::string, std::string> fFull2Short;  // filled by computeShortNames()
    
        /**
         * @brief check if a character is acceptable for an ID
         *
         * @param c
         * @return true is the character is acceptable for an ID
         */
        bool isIDChar(char c) const
        {
            return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9'));
        }
    
        /**
         * @brief remove all "/0x00" parts
         *
         * @param src
         * @return modified string
         */
        std::string remove0x00(const std::string& src) const
        {
            return std::regex_replace(src, std::regex("/0x00"), "");
        }
    
        /**
         * @brief replace all non ID char with '_' (one '_' may replace several non ID char)
         *
         * @param src
         * @return modified string
         */
        std::string str2ID(const std::string& src) const
        {
            std::string dst;
            bool need_underscore = false;
            for (char c : src) {
                if (isIDChar(c) || (c == '/')) {
                    if (need_underscore) {
                        dst.push_back('_');
                        need_underscore = false;
                    }
                    dst.push_back(c);
                } else {
                    need_underscore = true;
                }
            }
            return dst;
        }
    
        /**
         * @brief Keep only the last n slash-parts
         *
         * @param src
         * @param n : 1 indicates the last slash-part
         * @return modified string
         */
        std::string cut(const std::string& src, int n) const
        {
            std::string rdst;
            for (int i = int(src.length())-1; i >= 0; i--) {
                char c = src[i];
                if (c != '/') {
                    rdst.push_back(c);
                } else if (n == 1) {
                    std::string dst;
                    for (int j = int(rdst.length())-1; j >= 0; j--) {
                        dst.push_back(rdst[j]);
                    }
                    return dst;
                } else {
                    n--;
                    rdst.push_back(c);
                }
            }
            return src;
        }
    
        void addFullPath(const std::string& label) { fFullPaths.push_back(buildPath(label)); }
    
        /**
         * @brief Compute the mapping between full path and short names
         */
        void computeShortNames()
        {
            std::vector<std::string>           uniquePaths;  // all full paths transformed but made unique with a prefix
            std::map<std::string, std::string> unique2full;  // all full paths transformed but made unique with a prefix
            char num_buffer[16];
            int pnum = 0;
            
            for (const auto& s : fFullPaths) {
                // Using sprintf since Teensy does not have the std::to_string function
                sprintf(num_buffer, "%d", pnum++);
                std::string u = "/P" + std::string(num_buffer) + str2ID(remove0x00(s));
                uniquePaths.push_back(u);
                unique2full[u] = s;  // remember the full path associated to a unique path
            }
        
            std::map<std::string, int> uniquePath2level;                // map path to level
            for (const auto& s : uniquePaths) uniquePath2level[s] = 1;   // we init all levels to 1
            bool have_collisions = true;
        
            while (have_collisions) {
                // compute collision list
                std::set<std::string>              collisionSet;
                std::map<std::string, std::string> short2full;
                have_collisions = false;
                for (const auto& it : uniquePath2level) {
                    std::string u = it.first;
                    int n = it.second;
                    std::string shortName = cut(u, n);
                    auto p = short2full.find(shortName);
                    if (p == short2full.end()) {
                        // no collision
                        short2full[shortName] = u;
                    } else {
                        // we have a collision, add the two paths to the collision set
                        have_collisions = true;
                        collisionSet.insert(u);
                        collisionSet.insert(p->second);
                    }
                }
                for (const auto& s : collisionSet) uniquePath2level[s]++;  // increase level of colliding path
            }
        
            for (const auto& it : uniquePath2level) {
                std::string u = it.first;
                int n = it.second;
                std::string shortName = replaceCharList(cut(u, n), {'/'}, '_');
                fFull2Short[unique2full[u]] = shortName;
            }
        }
    
        std::string replaceCharList(const std::string& str, const std::vector<char>& ch1, char ch2)
        {
            auto beg = ch1.begin();
            auto end = ch1.end();
            std::string res = str;
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) res[i] = ch2;
            }
            return res;
        }
     
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        // Return true for the first level of groups
        bool pushLabel(const std::string& label) { fControlsLevel.push_back(label); return fControlsLevel.size() == 1;}
    
        // Return true for the last level of groups
        bool popLabel() { fControlsLevel.pop_back(); return fControlsLevel.size() == 0; }
    
        std::string buildPath(const std::string& label)
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res = res + fControlsLevel[i] + "/";
            }
            res += label;
            return replaceCharList(res, {' ', '#', '*', ',', '?', '[', ']', '{', '}', '(', ')'}, '_');
        }
    
};

#endif  // __PathBuilder__
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface.
 *
 * This class creates:
 * - a map of 'labels' and zones for each UI item.
 * - a map of unique 'shortname' (built so that they never collide) and zones for each UI item
 * - a map of complete hierarchical 'paths' and zones for each UI item
 *
 * Simple 'labels', 'shortname' and complete 'paths' (to fully discriminate between possible same
 * 'labels' at different location in the UI hierachy) can be used to access a given parameter.
 ******************************************************************************/

class FAUST_API MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
        // Shortname zone map
        std::map<std::string, FAUSTFLOAT*> fShortnameZoneMap;
    
        // Full path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        void addZoneLabel(const std::string& label, FAUSTFLOAT* zone)
        {
            std::string path = buildPath(label);
            fFullPaths.push_back(path);
            fPathZoneMap[path] = zone;
            fLabelZoneMap[label] = zone;
        }
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            if (popLabel()) {
                // Shortnames can be computed when all fullnames are known
                computeShortNames();
                // Fill 'shortname' map
                for (const auto& it : fFullPaths) {
                    fShortnameZoneMap[fFull2Short[it]] = fPathZoneMap[it];
                }
            }
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
    
        //-------------------------------------------------------------------------------
        // Public API
        //-------------------------------------------------------------------------------
    
        /**
         * Set the param value.
         *
         * @param str - the UI parameter label/shortname/path
         * @param value - the UI parameter value
         *
         */
        void setParamValue(const std::string& str, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                *fPathZoneMap[str] = value;
            } else if (fShortnameZoneMap.find(str) != fShortnameZoneMap.end()) {
                *fShortnameZoneMap[str] = value;
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                *fLabelZoneMap[str] = value;
            } else {
                fprintf(stderr, "ERROR : setParamValue '%s' not found\n", str.c_str());
            }
        }
        
        /**
         * Return the param value.
         *
         * @param str - the UI parameter label/shortname/path
         *
         * @return the param value.
         */
        FAUSTFLOAT getParamValue(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return *fPathZoneMap[str];
            } else if (fShortnameZoneMap.find(str) != fShortnameZoneMap.end()) {
                return *fShortnameZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[str];
            } else {
                fprintf(stderr, "ERROR : getParamValue '%s' not found\n", str.c_str());
                return 0;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getFullpathMap() { return fPathZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getShortnameMap() { return fShortnameZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getLabelMap() { return fLabelZoneMap; }
            
        /**
         * Return the number of parameters in the UI.
         *
         * @return the number of parameters
         */
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        /**
         * Return the param path.
         *
         * @param index - the UI parameter index
         *
         * @return the param path
         */
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param shortname.
         *
         * @param index - the UI parameter index
         *
         * @return the param shortname
         */
        std::string getParamShortname(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return "";
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamShortname1(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param label.
         *
         * @param index - the UI parameter index
         *
         * @return the param label
         */
        std::string getParamLabel(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return "";
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamLabel1(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param path.
         *
         * @param zone - the UI parameter memory zone
         *
         * @return the param path
         */
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        /**
         * Return the param memory zone.
         *
         * @param zone - the UI parameter label/shortname/path
         *
         * @return the param path
         */
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            } else if (fShortnameZoneMap.find(str) != fShortnameZoneMap.end()) {
                return fShortnameZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        /**
         * Return the param memory zone.
         *
         * @param zone - the UI parameter index
         *
         * @return the param path
         */
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
    
};

#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h *******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__


/**
 The base class of Meta handler to be used in dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct FAUST_API Meta {
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h ********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>
#include <cstdint>


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct FAUST_API UI;
struct FAUST_API Meta;

/**
 * DSP memory manager.
 */

struct FAUST_API dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    /**
     * Inform the Memory Manager with the number of expected memory zones.
     * @param count - the number of expected memory zones
     */
    virtual void begin(size_t /*count*/) {}
    
    /**
     * Give the Memory Manager information on a given memory zone.
     * @param size - the size in bytes of the memory zone
     * @param reads - the number of Read access to the zone used to compute one frame
     * @param writes - the number of Write access to the zone used to compute one frame
     */
    virtual void info(size_t /*size*/, size_t /*reads*/, size_t /*writes*/) {}

    /**
     * Inform the Memory Manager that all memory zones have been described,
     * to possibly start a 'compute the best allocation strategy' step.
     */
    virtual void end() {}
    
    /**
     * Allocate a memory zone.
     * @param size - the memory zone size in bytes
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Destroy a memory zone.
     * @param ptr - the memory zone pointer to be deallocated
     */
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class FAUST_API dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class FAUST_API decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class FAUST_API dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        /* Return factory name */
        virtual std::string getName() = 0;
    
        /* Return factory SHA key */
        virtual std::string getSHAKey() = 0;
    
        /* Return factory expanded DSP code */
        virtual std::string getDSPCode() = 0;
    
        /* Return factory compile options */
        virtual std::string getCompileOptions() = 0;
    
        /* Get the Faust DSP factory list of library dependancies */
        virtual std::vector<std::string> getLibraryList() = 0;
    
        /* Get the list of all used includes */
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        /* Get warning messages list for a given compilation */
        virtual std::vector<std::string> getWarningMessages() = 0;
    
        /* Create a new DSP instance, to be deleted with C++ 'delete' */
        virtual dsp* createDSPInstance() = 0;
    
        /* Static tables initialization, possibly implemened in sub-classes*/
        virtual void classInit(int sample_rate) {};
    
        /* Set a custom memory manager to be used when creating instances */
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
    
        /* Return the currently set custom memory manager */
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class FAUST_API ScopedNoDenormals {
    
    private:
    
        intptr_t fpsr = 0;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            // The volatile keyword here is needed to workaround a bug in AppleClang 13.0
            // which aggressively optimises away the variable otherwise
            volatile uint32_t fpsr_w = static_cast<uint32_t>(fpsr_aux);
            _mm_setcsr(fpsr_w);
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined (__SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #elif defined (__SSE__)
        #if defined (__SSE2__)
            intptr_t mask = 0x8040;
        #else
            intptr_t mask = 0x8000;
        #endif
        #else
            intptr_t mask = 0x0000;
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals ftz_scope;

#endif

/************************** END dsp.h **************************/

//?#include "FaustParameters.h"

// BEGIN-FAUSTDSP


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS VFDN
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float VFDN_faustpower2_f(float value) {
	return value * value;
}

class VFDN : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst2;
	float fConst4;
	float fConst6;
	float fConst8;
	float fConst9;
	float fConst10;
	int iVec0[2];
	float fRec17[2];
	float fConst11;
	float fConst12;
	float fConst13;
	float fRec16[3];
	float fConst14;
	float fConst15;
	FAUSTFLOAT fHslider2;
	float fConst16;
	FAUSTFLOAT fHslider3;
	float fRec18[2];
	float fRec19[2];
	float fRec21[2];
	float fRec20[3];
	float fConst17;
	float fRec23[2];
	float fRec22[3];
	float fRec25[2];
	float fRec24[3];
	float fRec27[2];
	float fRec26[3];
	float fRec29[2];
	float fRec28[3];
	float fRec31[2];
	float fRec30[3];
	float fRec33[2];
	float fRec32[3];
	float fRec35[2];
	float fRec34[3];
	float fRec37[2];
	float fRec36[3];
	float fRec39[2];
	float fRec38[3];
	float fRec41[2];
	float fRec40[3];
	float fRec43[2];
	float fRec42[3];
	float fRec45[2];
	float fRec44[3];
	float fRec47[2];
	float fRec46[3];
	float fRec49[2];
	float fRec48[3];
	float fRec51[2];
	float fRec50[3];
	float fRec53[2];
	float fRec52[3];
	float fRec55[2];
	float fRec54[3];
	float fRec57[2];
	float fRec56[3];
	float fRec59[2];
	float fRec58[3];
	float fRec61[2];
	float fRec60[3];
	float fRec63[2];
	float fRec62[3];
	float fRec65[2];
	float fRec64[3];
	float fRec67[2];
	float fRec66[3];
	float fRec69[2];
	float fRec68[3];
	float fRec71[2];
	float fRec70[3];
	float fRec73[2];
	float fRec72[3];
	float fRec75[2];
	float fRec74[3];
	float fRec77[2];
	float fRec76[3];
	float fRec79[2];
	float fRec78[3];
	float fRec81[2];
	float fRec80[3];
	int IOTA0;
	float fVec1[16384];
	float fRec0[3];
	float fVec2[16384];
	float fRec1[3];
	float fVec3[16384];
	float fRec2[3];
	float fVec4[16384];
	float fRec3[3];
	float fVec5[16384];
	float fRec4[3];
	float fVec6[16384];
	float fRec5[3];
	float fVec7[16384];
	float fRec6[3];
	float fVec8[16384];
	float fRec7[3];
	float fVec9[16384];
	float fRec8[3];
	float fVec10[16384];
	float fRec9[3];
	float fVec11[16384];
	float fRec10[3];
	float fVec12[16384];
	float fRec11[3];
	float fVec13[16384];
	float fRec12[3];
	float fVec14[16384];
	float fRec13[3];
	float fVec15[16384];
	float fRec14[3];
	float fVec16[16384];
	float fRec15[3];
	
 public:
	VFDN() {}

	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.2");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/tabulateNd", "Copyright (C) 2023 Bart Brouns <bart@magnetophon.nl>");
		m->declare("basics.lib/version", "0.10");
		m->declare("compile_options", "-a faustMinimal.h -lang cpp -i -inpl -ct 1 -cn VFDN -es 1 -mcd 16 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("filename", "VFDN.dsp");
		m->declare("filters.lib/filterbank:author", "Julius O. Smith III");
		m->declare("filters.lib/filterbank:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/filterbank:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.6");
		m->declare("name", "VFDN");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.4");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.2");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.3");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		float fConst1 = std::tan(21991.148f / fConst0);
		fConst2 = 1.0f / fConst1;
		float fConst3 = (fConst2 + 1.0f) / fConst1 + 1.0f;
		fConst4 = 0.25f / fConst3;
		float fConst5 = VFDN_faustpower2_f(fConst1);
		fConst6 = 1.0f / fConst5;
		float fConst7 = fConst2 + 1.0f;
		fConst8 = 0.0f - 1.0f / (fConst1 * fConst7);
		fConst9 = 1.0f / fConst7;
		fConst10 = 1.0f - fConst2;
		fConst11 = 1.0f / fConst3;
		fConst12 = (fConst2 + -1.0f) / fConst1 + 1.0f;
		fConst13 = 2.0f * (1.0f - fConst6);
		fConst14 = 0.0f - 2.0f / fConst5;
		fConst15 = 1e+01f / fConst0;
		fConst16 = 6.2831855f / fConst0;
		fConst17 = 0.29411766f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(-4e+01f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.02f);
		fHslider3 = FAUSTFLOAT(5.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec17[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 3; l2 = l2 + 1) {
			fRec16[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec18[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec19[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec21[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec20[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec23[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec22[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec25[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec24[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec27[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec26[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec29[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec28[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec31[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec30[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec33[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec32[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec35[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec34[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec37[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec36[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec39[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec38[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec41[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec40[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec43[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec42[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec45[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec44[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec47[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec46[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec49[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec48[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec51[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec50[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec53[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec52[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec55[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec54[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec57[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec56[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec59[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec58[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec61[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec60[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec63[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec62[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec65[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec64[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec67[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec66[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec69[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec68[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec71[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec70[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec73[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 3; l58 = l58 + 1) {
			fRec72[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec75[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 3; l60 = l60 + 1) {
			fRec74[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec77[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 3; l62 = l62 + 1) {
			fRec76[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec79[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 3; l64 = l64 + 1) {
			fRec78[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec81[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 3; l66 = l66 + 1) {
			fRec80[l66] = 0.0f;
		}
		IOTA0 = 0;
		for (int l67 = 0; l67 < 16384; l67 = l67 + 1) {
			fVec1[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 3; l68 = l68 + 1) {
			fRec0[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 16384; l69 = l69 + 1) {
			fVec2[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 3; l70 = l70 + 1) {
			fRec1[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 16384; l71 = l71 + 1) {
			fVec3[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec2[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 16384; l73 = l73 + 1) {
			fVec4[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 3; l74 = l74 + 1) {
			fRec3[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 16384; l75 = l75 + 1) {
			fVec5[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 3; l76 = l76 + 1) {
			fRec4[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 16384; l77 = l77 + 1) {
			fVec6[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 3; l78 = l78 + 1) {
			fRec5[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 16384; l79 = l79 + 1) {
			fVec7[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 3; l80 = l80 + 1) {
			fRec6[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 16384; l81 = l81 + 1) {
			fVec8[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 3; l82 = l82 + 1) {
			fRec7[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 16384; l83 = l83 + 1) {
			fVec9[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 3; l84 = l84 + 1) {
			fRec8[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 16384; l85 = l85 + 1) {
			fVec10[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 3; l86 = l86 + 1) {
			fRec9[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 16384; l87 = l87 + 1) {
			fVec11[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 3; l88 = l88 + 1) {
			fRec10[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 16384; l89 = l89 + 1) {
			fVec12[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 3; l90 = l90 + 1) {
			fRec11[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 16384; l91 = l91 + 1) {
			fVec13[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 3; l92 = l92 + 1) {
			fRec12[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 16384; l93 = l93 + 1) {
			fVec14[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 3; l94 = l94 + 1) {
			fRec13[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 16384; l95 = l95 + 1) {
			fVec15[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 3; l96 = l96 + 1) {
			fRec14[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 16384; l97 = l97 + 1) {
			fVec16[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 3; l98 = l98 + 1) {
			fRec15[l98] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual VFDN* clone() {
		return new VFDN();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("VFDN");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(-4e+01f), FAUSTFLOAT(-7e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("mod_freq", &fHslider3, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("mod_width", &fHslider2, FAUSTFLOAT(0.02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.5f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("wet", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::pow(1e+01f, 0.05f * float(fHslider0));
		float fSlow1 = float(fHslider1);
		float fSlow2 = float(fHslider2);
		float fSlow3 = fConst16 * float(fHslider3);
		float fSlow4 = std::sin(fSlow3);
		float fSlow5 = std::cos(fSlow3);
		float fSlow6 = 1.0f - fSlow1;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			iVec0[0] = 1;
			fRec17[0] = fConst8 * fRec0[2] - fConst9 * (fConst10 * fRec17[1] - fConst2 * fRec0[1]);
			fRec16[0] = fRec17[0] - fConst11 * (fConst12 * fRec16[2] + fConst13 * fRec16[1]);
			fRec18[0] = fSlow4 * fRec19[1] + fSlow5 * fRec18[1];
			fRec19[0] = float(1 - iVec0[1]) + fSlow5 * fRec19[1] - fSlow4 * fRec18[1];
			float fTemp1 = fSlow2 * fRec18[0] + 2.0f;
			float fTemp2 = 0.0f - 11895.154f * fTemp1;
			fRec21[0] = 0.0f - fConst9 * (fConst10 * fRec21[1] - (fRec0[1] + fRec0[2]));
			fRec20[0] = fRec21[0] - fConst11 * (fConst12 * fRec20[2] + fConst13 * fRec20[1]);
			float fTemp3 = (fConst6 * fRec16[0] + fConst14 * fRec16[1] + fConst6 * fRec16[2]) * std::exp(fConst15 * fTemp2) + (fRec20[2] + fRec20[0] + 2.0f * fRec20[1]) * std::exp(fConst17 * fTemp2);
			fRec23[0] = fConst8 * fRec8[2] - fConst9 * (fConst10 * fRec23[1] - fConst2 * fRec8[1]);
			fRec22[0] = fRec23[0] - fConst11 * (fConst12 * fRec22[2] + fConst13 * fRec22[1]);
			float fTemp4 = 0.0f - 13380.322f * fTemp1;
			fRec25[0] = 0.0f - fConst9 * (fConst10 * fRec25[1] - (fRec8[1] + fRec8[2]));
			fRec24[0] = fRec25[0] - fConst11 * (fConst12 * fRec24[2] + fConst13 * fRec24[1]);
			float fTemp5 = (fConst6 * fRec22[0] + fConst14 * fRec22[1] + fConst6 * fRec22[2]) * std::exp(fConst15 * fTemp4) + (fRec24[2] + fRec24[0] + 2.0f * fRec24[1]) * std::exp(fConst17 * fTemp4);
			float fTemp6 = fTemp3 + fTemp5;
			fRec27[0] = fConst8 * fRec4[2] - fConst9 * (fConst10 * fRec27[1] - fConst2 * fRec4[1]);
			fRec26[0] = fRec27[0] - fConst11 * (fConst12 * fRec26[2] + fConst13 * fRec26[1]);
			float fTemp7 = 0.0f - 10009.337f * fTemp1;
			fRec29[0] = 0.0f - fConst9 * (fConst10 * fRec29[1] - (fRec4[1] + fRec4[2]));
			fRec28[0] = fRec29[0] - fConst11 * (fConst12 * fRec28[2] + fConst13 * fRec28[1]);
			float fTemp8 = (fConst6 * fRec26[0] + fConst14 * fRec26[1] + fConst6 * fRec26[2]) * std::exp(fConst15 * fTemp7) + (fRec28[2] + fRec28[0] + 2.0f * fRec28[1]) * std::exp(fConst17 * fTemp7);
			fRec31[0] = fConst8 * fRec12[2] - fConst9 * (fConst10 * fRec31[1] - fConst2 * fRec12[1]);
			fRec30[0] = fRec31[0] - fConst11 * (fConst12 * fRec30[2] + fConst13 * fRec30[1]);
			float fTemp9 = 0.0f - 13373.414f * fTemp1;
			fRec33[0] = 0.0f - fConst9 * (fConst10 * fRec33[1] - (fRec12[1] + fRec12[2]));
			fRec32[0] = fRec33[0] - fConst11 * (fConst12 * fRec32[2] + fConst13 * fRec32[1]);
			float fTemp10 = (fConst6 * fRec30[0] + fConst14 * fRec30[1] + fConst6 * fRec30[2]) * std::exp(fConst15 * fTemp9) + (fRec32[2] + fRec32[0] + 2.0f * fRec32[1]) * std::exp(fConst17 * fTemp9);
			float fTemp11 = fTemp8 + fTemp10;
			float fTemp12 = fTemp6 + fTemp11;
			fRec35[0] = fConst8 * fRec2[2] - fConst9 * (fConst10 * fRec35[1] - fConst2 * fRec2[1]);
			fRec34[0] = fRec35[0] - fConst11 * (fConst12 * fRec34[2] + fConst13 * fRec34[1]);
			float fTemp13 = 0.0f - 4766.351f * fTemp1;
			fRec37[0] = 0.0f - fConst9 * (fConst10 * fRec37[1] - (fRec2[1] + fRec2[2]));
			fRec36[0] = fRec37[0] - fConst11 * (fConst12 * fRec36[2] + fConst13 * fRec36[1]);
			float fTemp14 = (fConst6 * fRec34[0] + fConst14 * fRec34[1] + fConst6 * fRec34[2]) * std::exp(fConst15 * fTemp13) + (fRec36[2] + fRec36[0] + 2.0f * fRec36[1]) * std::exp(fConst17 * fTemp13);
			fRec39[0] = fConst8 * fRec10[2] - fConst9 * (fConst10 * fRec39[1] - fConst2 * fRec10[1]);
			fRec38[0] = fRec39[0] - fConst11 * (fConst12 * fRec38[2] + fConst13 * fRec38[1]);
			float fTemp15 = 0.0f - 5084.108f * fTemp1;
			fRec41[0] = 0.0f - fConst9 * (fConst10 * fRec41[1] - (fRec10[1] + fRec10[2]));
			fRec40[0] = fRec41[0] - fConst11 * (fConst12 * fRec40[2] + fConst13 * fRec40[1]);
			float fTemp16 = (fConst6 * fRec38[0] + fConst14 * fRec38[1] + fConst6 * fRec38[2]) * std::exp(fConst15 * fTemp15) + (fRec40[2] + fRec40[0] + 2.0f * fRec40[1]) * std::exp(fConst17 * fTemp15);
			float fTemp17 = fTemp14 + fTemp16;
			fRec43[0] = fConst8 * fRec6[2] - fConst9 * (fConst10 * fRec43[1] - fConst2 * fRec6[1]);
			fRec42[0] = fRec43[0] - fConst11 * (fConst12 * fRec42[2] + fConst13 * fRec42[1]);
			float fTemp18 = 0.0f - 6341.3193f * fTemp1;
			fRec45[0] = 0.0f - fConst9 * (fConst10 * fRec45[1] - (fRec6[1] + fRec6[2]));
			fRec44[0] = fRec45[0] - fConst11 * (fConst12 * fRec44[2] + fConst13 * fRec44[1]);
			float fTemp19 = (fConst6 * fRec42[0] + fConst14 * fRec42[1] + fConst6 * fRec42[2]) * std::exp(fConst15 * fTemp18) + (fRec44[2] + fRec44[0] + 2.0f * fRec44[1]) * std::exp(fConst17 * fTemp18);
			fRec47[0] = fConst8 * fRec14[2] - fConst9 * (fConst10 * fRec47[1] - fConst2 * fRec14[1]);
			fRec46[0] = fRec47[0] - fConst11 * (fConst12 * fRec46[2] + fConst13 * fRec46[1]);
			float fTemp20 = 0.0f - 11750.092f * fTemp1;
			fRec49[0] = 0.0f - fConst9 * (fConst10 * fRec49[1] - (fRec14[1] + fRec14[2]));
			fRec48[0] = fRec49[0] - fConst11 * (fConst12 * fRec48[2] + fConst13 * fRec48[1]);
			float fTemp21 = (fConst6 * fRec46[0] + fConst14 * fRec46[1] + fConst6 * fRec46[2]) * std::exp(fConst15 * fTemp20) + (fRec48[2] + fRec48[0] + 2.0f * fRec48[1]) * std::exp(fConst17 * fTemp20);
			float fTemp22 = fTemp19 + fTemp21;
			float fTemp23 = fTemp17 + fTemp22;
			float fTemp24 = fTemp12 + fTemp23;
			fRec51[0] = fConst8 * fRec1[2] - fConst9 * (fConst10 * fRec51[1] - fConst2 * fRec1[1]);
			fRec50[0] = fRec51[0] - fConst11 * (fConst12 * fRec50[2] + fConst13 * fRec50[1]);
			float fTemp25 = 0.0f - 12841.517f * fTemp1;
			fRec53[0] = 0.0f - fConst9 * (fConst10 * fRec53[1] - (fRec1[1] + fRec1[2]));
			fRec52[0] = fRec53[0] - fConst11 * (fConst12 * fRec52[2] + fConst13 * fRec52[1]);
			float fTemp26 = (fConst6 * fRec50[0] + fConst14 * fRec50[1] + fConst6 * fRec50[2]) * std::exp(fConst15 * fTemp25) + (fRec52[2] + fRec52[0] + 2.0f * fRec52[1]) * std::exp(fConst17 * fTemp25);
			fRec55[0] = fConst8 * fRec9[2] - fConst9 * (fConst10 * fRec55[1] - fConst2 * fRec9[1]);
			fRec54[0] = fRec55[0] - fConst11 * (fConst12 * fRec54[2] + fConst13 * fRec54[1]);
			float fTemp27 = 0.0f - 13456.308f * fTemp1;
			fRec57[0] = 0.0f - fConst9 * (fConst10 * fRec57[1] - (fRec9[1] + fRec9[2]));
			fRec56[0] = fRec57[0] - fConst11 * (fConst12 * fRec56[2] + fConst13 * fRec56[1]);
			float fTemp28 = (fConst6 * fRec54[0] + fConst14 * fRec54[1] + fConst6 * fRec54[2]) * std::exp(fConst15 * fTemp27) + (fRec56[2] + fRec56[0] + 2.0f * fRec56[1]) * std::exp(fConst17 * fTemp27);
			float fTemp29 = fTemp26 + fTemp28;
			fRec59[0] = fConst8 * fRec5[2] - fConst9 * (fConst10 * fRec59[1] - fConst2 * fRec5[1]);
			fRec58[0] = fRec59[0] - fConst11 * (fConst12 * fRec58[2] + fConst13 * fRec58[1]);
			float fTemp30 = 0.0f - 4462.4097f * fTemp1;
			fRec61[0] = 0.0f - fConst9 * (fConst10 * fRec61[1] - (fRec5[1] + fRec5[2]));
			fRec60[0] = fRec61[0] - fConst11 * (fConst12 * fRec60[2] + fConst13 * fRec60[1]);
			float fTemp31 = (fConst6 * fRec58[0] + fConst14 * fRec58[1] + fConst6 * fRec58[2]) * std::exp(fConst15 * fTemp30) + (fRec60[2] + fRec60[0] + 2.0f * fRec60[1]) * std::exp(fConst17 * fTemp30);
			fRec63[0] = fConst8 * fRec13[2] - fConst9 * (fConst10 * fRec63[1] - fConst2 * fRec13[1]);
			fRec62[0] = fRec63[0] - fConst11 * (fConst12 * fRec62[2] + fConst13 * fRec62[1]);
			float fTemp32 = 0.0f - 8482.724f * fTemp1;
			fRec65[0] = 0.0f - fConst9 * (fConst10 * fRec65[1] - (fRec13[1] + fRec13[2]));
			fRec64[0] = fRec65[0] - fConst11 * (fConst12 * fRec64[2] + fConst13 * fRec64[1]);
			float fTemp33 = (fConst6 * fRec62[0] + fConst14 * fRec62[1] + fConst6 * fRec62[2]) * std::exp(fConst15 * fTemp32) + (fRec64[2] + fRec64[0] + 2.0f * fRec64[1]) * std::exp(fConst17 * fTemp32);
			float fTemp34 = fTemp31 + fTemp33;
			float fTemp35 = fTemp29 + fTemp34;
			fRec67[0] = fConst8 * fRec3[2] - fConst9 * (fConst10 * fRec67[1] - fConst2 * fRec3[1]);
			fRec66[0] = fRec67[0] - fConst11 * (fConst12 * fRec66[2] + fConst13 * fRec66[1]);
			float fTemp36 = 0.0f - 12917.502f * fTemp1;
			fRec69[0] = 0.0f - fConst9 * (fConst10 * fRec69[1] - (fRec3[1] + fRec3[2]));
			fRec68[0] = fRec69[0] - fConst11 * (fConst12 * fRec68[2] + fConst13 * fRec68[1]);
			float fTemp37 = (fConst6 * fRec66[0] + fConst14 * fRec66[1] + fConst6 * fRec66[2]) * std::exp(fConst15 * fTemp36) + (fRec68[2] + fRec68[0] + 2.0f * fRec68[1]) * std::exp(fConst17 * fTemp36);
			fRec71[0] = fConst8 * fRec11[2] - fConst9 * (fConst10 * fRec71[1] - fConst2 * fRec11[1]);
			fRec70[0] = fRec71[0] - fConst11 * (fConst12 * fRec70[2] + fConst13 * fRec70[1]);
			float fTemp38 = 0.0f - 13511.569f * fTemp1;
			fRec73[0] = 0.0f - fConst9 * (fConst10 * fRec73[1] - (fRec11[1] + fRec11[2]));
			fRec72[0] = fRec73[0] - fConst11 * (fConst12 * fRec72[2] + fConst13 * fRec72[1]);
			float fTemp39 = (fConst6 * fRec70[0] + fConst14 * fRec70[1] + fConst6 * fRec70[2]) * std::exp(fConst15 * fTemp38) + (fRec72[2] + fRec72[0] + 2.0f * fRec72[1]) * std::exp(fConst17 * fTemp38);
			float fTemp40 = fTemp37 + fTemp39;
			fRec75[0] = fConst8 * fRec7[2] - fConst9 * (fConst10 * fRec75[1] - fConst2 * fRec7[1]);
			fRec74[0] = fRec75[0] - fConst11 * (fConst12 * fRec74[2] + fConst13 * fRec74[1]);
			float fTemp41 = 0.0f - 9118.237f * fTemp1;
			fRec77[0] = 0.0f - fConst9 * (fConst10 * fRec77[1] - (fRec7[1] + fRec7[2]));
			fRec76[0] = fRec77[0] - fConst11 * (fConst12 * fRec76[2] + fConst13 * fRec76[1]);
			float fTemp42 = (fConst6 * fRec74[0] + fConst14 * fRec74[1] + fConst6 * fRec74[2]) * std::exp(fConst15 * fTemp41) + (fRec76[2] + fRec76[0] + 2.0f * fRec76[1]) * std::exp(fConst17 * fTemp41);
			fRec79[0] = fConst8 * fRec15[2] - fConst9 * (fConst10 * fRec79[1] - fConst2 * fRec15[1]);
			fRec78[0] = fRec79[0] - fConst11 * (fConst12 * fRec78[2] + fConst13 * fRec78[1]);
			float fTemp43 = 0.0f - 4918.322f * fTemp1;
			fRec81[0] = 0.0f - fConst9 * (fConst10 * fRec81[1] - (fRec15[1] + fRec15[2]));
			fRec80[0] = fRec81[0] - fConst11 * (fConst12 * fRec80[2] + fConst13 * fRec80[1]);
			float fTemp44 = (fConst6 * fRec78[0] + fConst14 * fRec78[1] + fConst6 * fRec78[2]) * std::exp(fConst15 * fTemp43) + (fRec80[2] + fRec80[0] + 2.0f * fRec80[1]) * std::exp(fConst17 * fTemp43);
			float fTemp45 = fTemp42 + fTemp44;
			float fTemp46 = fTemp40 + fTemp45;
			float fTemp47 = fTemp35 + fTemp46;
			fVec1[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp24 + fTemp47);
			fRec0[0] = fVec1[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1722.0f * fTemp1 + -1.0f)))) & 16383];
			fVec2[IOTA0 & 16383] = fTemp0 - fConst4 * (fTemp47 - fTemp24);
			fRec1[0] = fVec2[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1859.0f * fTemp1 + -1.0f)))) & 16383];
			float fTemp48 = fTemp12 - fTemp23;
			float fTemp49 = fTemp35 - fTemp46;
			fVec3[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp48 + fTemp49);
			fRec2[0] = fVec3[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 6.9e+02f * fTemp1 + -1.0f)))) & 16383];
			fVec4[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp48 - fTemp49);
			fRec3[0] = fVec4[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1.87e+03f * fTemp1 + -1.0f)))) & 16383];
			float fTemp50 = fTemp11 - fTemp6;
			float fTemp51 = fTemp17 - fTemp22;
			float fTemp52 = fTemp50 - fTemp51;
			float fTemp53 = fTemp34 - fTemp29;
			float fTemp54 = fTemp40 - fTemp45;
			float fTemp55 = fTemp53 - fTemp54;
			fVec5[IOTA0 & 16383] = fTemp0 - fConst4 * (fTemp52 + fTemp55);
			fRec4[0] = fVec5[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1449.0f * fTemp1 + -1.0f)))) & 16383];
			fVec6[IOTA0 & 16383] = fTemp0 - fConst4 * (fTemp52 - fTemp55);
			fRec5[0] = fVec6[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 646.0f * fTemp1 + -1.0f)))) & 16383];
			float fTemp56 = fTemp50 + fTemp51;
			float fTemp57 = fTemp53 + fTemp54;
			fVec7[IOTA0 & 16383] = fTemp0 - fConst4 * (fTemp56 + fTemp57);
			fRec6[0] = fVec7[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 918.0f * fTemp1 + -1.0f)))) & 16383];
			fVec8[IOTA0 & 16383] = fTemp0 - fConst4 * (fTemp56 - fTemp57);
			fRec7[0] = fVec8[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1.32e+03f * fTemp1 + -1.0f)))) & 16383];
			float fTemp58 = fTemp3 - fTemp5;
			float fTemp59 = fTemp8 - fTemp10;
			float fTemp60 = fTemp58 + fTemp59;
			float fTemp61 = fTemp14 - fTemp16;
			float fTemp62 = fTemp19 - fTemp21;
			float fTemp63 = fTemp61 + fTemp62;
			float fTemp64 = fTemp60 + fTemp63;
			float fTemp65 = fTemp28 - fTemp26;
			float fTemp66 = fTemp33 - fTemp31;
			float fTemp67 = fTemp65 + fTemp66;
			float fTemp68 = fTemp39 - fTemp37;
			float fTemp69 = fTemp42 - fTemp44;
			float fTemp70 = fTemp68 - fTemp69;
			float fTemp71 = fTemp67 + fTemp70;
			fVec9[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp64 - fTemp71);
			fRec8[0] = fVec9[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1937.0f * fTemp1 + -1.0f)))) & 16383];
			fVec10[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp64 + fTemp71);
			fRec9[0] = fVec10[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1948.0f * fTemp1 + -1.0f)))) & 16383];
			float fTemp72 = fTemp60 - fTemp63;
			float fTemp73 = fTemp67 - fTemp70;
			fVec11[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp72 - fTemp73);
			fRec10[0] = fVec11[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 736.0f * fTemp1 + -1.0f)))) & 16383];
			fVec12[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp72 + fTemp73);
			fRec11[0] = fVec12[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1956.0f * fTemp1 + -1.0f)))) & 16383];
			float fTemp74 = fTemp58 - fTemp59;
			float fTemp75 = fTemp61 - fTemp62;
			float fTemp76 = fTemp74 + fTemp75;
			float fTemp77 = fTemp65 - fTemp66;
			float fTemp78 = fTemp68 + fTemp69;
			float fTemp79 = fTemp77 + fTemp78;
			fVec13[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp76 - fTemp79);
			fRec12[0] = fVec13[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1936.0f * fTemp1 + -1.0f)))) & 16383];
			fVec14[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp76 + fTemp79);
			fRec13[0] = fVec14[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1228.0f * fTemp1 + -1.0f)))) & 16383];
			float fTemp80 = fTemp74 - fTemp75;
			float fTemp81 = fTemp77 - fTemp78;
			fVec15[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp80 - fTemp81);
			fRec14[0] = fVec15[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 1701.0f * fTemp1 + -1.0f)))) & 16383];
			fVec16[IOTA0 & 16383] = fTemp0 + fConst4 * (fTemp80 + fTemp81);
			fRec15[0] = fVec16[(IOTA0 - int(std::min<float>(8192.0f, std::max<float>(0.0f, 712.0f * fTemp1 + -1.0f)))) & 16383];
			output0[i0] = FAUSTFLOAT(fSlow0 * (fSlow1 * (fRec0[0] + fRec1[0] + fRec2[0] + fRec3[0] + fRec4[0] + fRec5[0] + fRec6[0] + fRec7[0] + fRec8[0] + fRec9[0] + fRec10[0] + fRec11[0] + fRec12[0] + fRec13[0] + fRec14[0] + fRec15[0]) + fSlow6 * fTemp0));
			iVec0[1] = iVec0[0];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			IOTA0 = IOTA0 + 1;
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
		}
	}

};

// END-FAUSTDSP

#endif
