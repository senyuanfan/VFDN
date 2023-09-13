/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== layout.xml ==================
static const unsigned char temp_binary_data_0[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
"\r\n"
"<magic>\r\n"
"  <Styles>\r\n"
"    <Style name=\"default\">\r\n"
"      <Nodes/>\r\n"
"      <Classes>\r\n"
"        <plot-view border=\"2\" background-color=\"black\" border-color=\"silver\" display=\"contents\"/>\r\n"
"        <nomargin margin=\"0\" padding=\"0\" border=\"0\"/>\r\n"
"        <group margin=\"5\" padding=\"5\" border=\"2\" flex-direction=\"column\"/>\r\n"
"        <transparent background-color=\"transparentblack\"/>\r\n"
"      </Classes>\r\n"
"      <Types>\r\n"
"        <Slider border=\"0\" slider-textbox=\"textbox-below\"/>\r\n"
"        <ToggleButton border=\"0\" max-height=\"50\" caption-size=\"0\" text=\"Active\"/>\r\n"
"        <TextButton border=\"0\" max-height=\"50\" caption-size=\"0\"/>\r\n"
"        <ComboBox border=\"0\" max-height=\"50\" caption-size=\"0\"/>\r\n"
"        <Plot border=\"0\" margin=\"0\" padding=\"0\" background-color=\"00000000\"\r\n"
"              radius=\"0\"/>\r\n"
"        <XYDragComponent border=\"0\" margin=\"0\" padding=\"0\" background-color=\"00000000\"\r\n"
"                         radius=\"0\"/>\r\n"
"      </Types>\r\n"
"      <Palettes>\r\n"
"        <default/>\r\n"
"      </Palettes>\r\n"
"    </Style>\r\n"
"  </Styles>\r\n"
"  <View id=\"root\" resizable=\"1\" resize-corner=\"1\" flex-direction=\"column\"\r\n"
"        description=\"\" lookAndFeel=\"Skeuomorphic\" tab-caption=\"\" background-color=\"\">\r\n"
"    <View class=\"parameters nomargin\" lookAndFeel=\"\" background-color=\"FFDDDAC7\">\r\n"
"      <View flex-direction=\"column\" background-color=\"FFB4AA9B\">\r\n"
"        <Slider caption=\"Modulation Width\" parameter=\"VFDN:mod_width\" lookAndFeel=\"Skeuomorphic\"\r\n"
"                slider-text-background=\"FFFFFFFF\" slider-text=\"FF000000\" rotary-outline=\"\"\r\n"
"                rotary-fill=\"FFAD371E\" background-color=\"FF13924F\" caption-color=\"FFFFFFFF\"/>\r\n"
"        <Slider caption=\"Modulation Frequency\" parameter=\"VFDN:mod_freq\" lookAndFeel=\"Skeuomorphic\"\r\n"
"                slider-text-background=\"FFFFFFFF\" slider-text=\"FF000000\" rotary-fill=\"FF29B95C\"\r\n"
"                flex-align-self=\"stretch\" background-color=\"FFBC362F\" caption-color=\"FFFFFFFF\"/>\r\n"
"      </View>\r\n"
"      <View background-color=\"FFB4AA9B\">\r\n"
"        <Slider parameter=\"VFDN:wet\" lookAndFeel=\"LookAndFeel_V1\" background-color=\"FF463C9F\"\r\n"
"                caption-color=\"FFFFFFFF\" slider-track=\"FF424040\" slider-thumb=\"FFE4C828\"\r\n"
"                caption=\"Mix\"/>\r\n"
"      </View>\r\n"
"      <View background-color=\"FFB4AA9B\" border-color=\"\">\r\n"
"        <Slider caption=\"Gain (dB)\" parameter=\"VFDN:gain\" lookAndFeel=\"LookAndFeel_V1\"\r\n"
"                background-color=\"FFE2B640\" tab-color=\"\" border-color=\"\" caption-color=\"FFFFFFFF\"\r\n"
"                slider-track=\"FF535050\" slider-thumb=\"FF576BF2\"/>\r\n"
"      </View>\r\n"
"    </View>\r\n"
"  </View>\r\n"
"</magic>\r\n";

const char* layout_xml = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x14625582:  numBytes = 2598; return layout_xml;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "layout_xml"
};

const char* originalFilenames[] =
{
    "layout.xml"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
