module;

#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>

export module seewk.FontManager;

export struct GlyphInfo
{
    int width = 0;
    int height = 0;
    int bearingX = 0;
    int bearingY = 0;
    int advance = 0;
    std::vector<unsigned char> bitmap;
    int atlasX = 0;
    int atlasY = 0;
    int atlasOffsetX = 0;
    int atlasOffsetY = 0;
    void getUV(float atlasWidth, float atlasHeight,
               float &uStart, float &vStart,
               float &uEnd, float &vEnd) const
    {
        uStart = static_cast<float>(atlasOffsetX) / atlasWidth;
        vStart = static_cast<float>(atlasOffsetY) / atlasHeight;
        uEnd = static_cast<float>(atlasOffsetX + width) / atlasWidth;
        vEnd = static_cast<float>(atlasOffsetY + height) / atlasHeight;
    }
};

export struct AtlasInfo
{
    int width = 0;
    int height = 0;
    std::vector<unsigned char> data;
    std::unordered_map<char, GlyphInfo> glyphs;
};

export class FontManager
{
    FT_Library library;
    FT_Face face;
    std::unordered_map<char, GlyphInfo> glyphCache;

public:
    FontManager()
    {
        FT_Init_FreeType(&library);
        FT_New_Face(library, "./src/font/Roboto-Regular.ttf", 0, &face);
        FT_Set_Char_Size(face, 0, 16 * 64, 300, 300);
    }

    ~FontManager()
    {
        if (face)
            FT_Done_Face(face);
        if (library)
            FT_Done_FreeType(library);
    }

    const GlyphInfo &getGlyph(char c)
    {
        auto it = glyphCache.find(c);
        if (it != glyphCache.end())
        {
            return it->second;
        }

        FT_Load_Char(face, c, FT_LOAD_RENDER);
        FT_Bitmap &ftBitmap = face->glyph->bitmap;

        GlyphInfo info;
        info.width = ftBitmap.width;
        info.height = ftBitmap.rows;
        info.bearingX = face->glyph->bitmap_left;
        info.bearingY = face->glyph->bitmap_top;
        info.advance = face->glyph->advance.x >> 6;

        if (ftBitmap.width > 0 && ftBitmap.rows > 0)
        {
            info.bitmap.resize(ftBitmap.width * ftBitmap.rows);
            for (int y = 0; y < ftBitmap.rows; y++)
            {
                for (int x = 0; x < ftBitmap.width; x++)
                {
                    info.bitmap[y * ftBitmap.width + x] =
                        ftBitmap.buffer[y * ftBitmap.pitch + x];
                }
            }
        }

        glyphCache[c] = std::move(info);
        return glyphCache[c];
    }

    AtlasInfo generateAtlas(const std::string &chars = "", int charSize = 32)
    {
        std::string charsToRender = chars;
        if (charsToRender.empty())
        {

            for (char c = 32; c <= 126; c++)
            {
                charsToRender.push_back(c);
            }
        }

        const int CHAR_PER_ROW = 16;

        int numChars = charsToRender.size();
        int rows = (numChars + CHAR_PER_ROW - 1) / CHAR_PER_ROW;
        int atlasWidth = CHAR_PER_ROW * charSize;
        int atlasHeight = rows * charSize;

        std::vector<unsigned char> atlasData(atlasWidth * atlasHeight, 0);

        std::unordered_map<char, GlyphInfo> atlasGlyphs;

        int x = 0, y = 0;
        for (char c : charsToRender)
        {

            const GlyphInfo &glyph = getGlyph(c);

            if (glyph.width > 0 && glyph.height > 0)
            {

                int offsetX = x * charSize + (charSize - glyph.width) / 2;
                int offsetY = y * charSize + (charSize - glyph.height) / 2;

                for (int row = 0; row < glyph.height && row < charSize; row++)
                {
                    for (int col = 0; col < glyph.width && col < charSize; col++)
                    {
                        int atlasIdx = (offsetY + row) * atlasWidth + (offsetX + col);
                        int glyphIdx = row * glyph.width + col;
                        atlasData[atlasIdx] = glyph.bitmap[glyphIdx];
                    }
                }
            }

            GlyphInfo atlasGlyph = glyph;
            atlasGlyph.atlasX = x;
            atlasGlyph.atlasY = y;
            atlasGlyph.atlasOffsetX = x * charSize + (charSize - glyph.width) / 2;
            atlasGlyph.atlasOffsetY = y * charSize + (charSize - glyph.height) / 2;
            atlasGlyphs[c] = atlasGlyph;

            x++;
            if (x >= CHAR_PER_ROW)
            {
                x = 0;
                y++;
            }
        }

        AtlasInfo result;
        result.width = atlasWidth;
        result.height = atlasHeight;
        result.data = std::move(atlasData);
        result.glyphs = std::move(atlasGlyphs);

        return result;
    }
};
