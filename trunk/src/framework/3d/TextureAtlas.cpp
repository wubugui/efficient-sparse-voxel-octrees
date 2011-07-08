/*
 *  Copyright 2009-2010 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
#include "3d/TextureAtlas.hpp"
#include "base/Sort.hpp"

using namespace FW;

//------------------------------------------------------------------------

TextureAtlas::TextureAtlas(const ImageFormat& format)
:   m_format    (format),
    m_atlasSize (0)
{
}

//------------------------------------------------------------------------

TextureAtlas::~TextureAtlas(void)
{
}

//------------------------------------------------------------------------

void TextureAtlas::clear(void)
{
    if (m_items.getSize())
    {
        m_items.reset();
        m_itemHash.clear();
        m_atlasTexture = Texture();
    }
}

//------------------------------------------------------------------------

bool TextureAtlas::addTexture(const Texture& tex, int border, bool wrap)
{
    FW_ASSERT(border >= 0);
    const Image* image = tex.getImage();
    if (!image || min(image->getSize()) <= 0 || m_itemHash.contains(image))
        return false;

    m_itemHash.add(image, m_items.getSize());
    Item& item      = m_items.add();
    item.texture    = tex;
    item.border     = border;
    item.wrap       = wrap;
    item.size       = image->getSize() + border * 2;
    m_atlasTexture  = Texture();
    return true;
}

//------------------------------------------------------------------------

Vec2i TextureAtlas::getTexturePos(const Texture& tex)
{
    validate();
    S32* found = m_itemHash.search(tex.getImage());
    if (!found)
        return 0;

    const Item& item = m_items[*found];
    return item.pos + item.border;
}

//------------------------------------------------------------------------

void TextureAtlas::validate(void)
{
    if (!m_atlasTexture.exists())
    {
        layoutItems();
        if (!hasError())
            createAtlas();
    }
}

//------------------------------------------------------------------------

void TextureAtlas::layoutItems(void)
{
    // Select initial size.

    S32 totalArea = 0;
    for (int i = 0; i < m_items.getSize(); i++)
        totalArea += m_items[i].size.x * m_items[i].size.y;
    Vec2i canvas = (int)sqrt((F32)totalArea);

    // Sort items in descending order of height.

    Array<Vec2i> order(NULL, m_items.getSize());
    for (int i = 0; i < m_items.getSize(); i++)
        order[i] = Vec2i(-m_items[i].size.y, i);
    sort(0, m_items.getSize(), order.getPtr(), compareVec2i, swapVec2i);

    // Add items iteratively.

    Array<Vec4i> maxRects(Vec4i(0, 0, FW_S32_MAX, FW_S32_MAX));
    for (int itemIdx = 0; itemIdx < m_items.getSize(); itemIdx++)
    {
        Item& item = m_items[order[itemIdx].y];
        const Vec2i& s = item.size;

        // Select position.

        Vec2i bestPos = 0;
        Vec3i bestCost = FW_S32_MAX;
        for (int i = 0; i < maxRects.getSize(); i++)
        {
            const Vec4i& r = maxRects[i];
            if (r.x + s.x > r.z || r.y + s.y > r.w)
                continue;

            Vec3i cost;
            cost.x = max(canvas.x, r.x + s.x) * max(canvas.y, r.y + s.y); // Minimize canvas.
            cost.y = r.y + s.y; // Minimize Y.
            cost.z = r.x + s.x; // Minimize X.

            if (cost.x < bestCost.x || (cost.x == bestCost.x && (cost.y < bestCost.y || (cost.y == bestCost.y && cost.z < bestCost.z))))
            {
                bestPos = r.getXY();
                bestCost = cost;
            }
        }

        item.pos = bestPos;
        canvas = max(canvas, bestPos + s);
        Vec4i t(bestPos, bestPos + s);

        // Split maximal rectangles.

        for (int i = maxRects.getSize() - 1; i >= 0; i--)
        {
            Vec4i r = maxRects[i];
            if (t.x >= r.z || t.y >= r.w || t.z <= r.x || t.w <= r.y)
                continue;

            maxRects.removeSwap(i);
            if (t.x > r.x) maxRects.add(Vec4i(r.x, r.y, t.x, r.w));
            if (t.y > r.y) maxRects.add(Vec4i(r.x, r.y, r.z, t.y));
            if (t.z < r.z) maxRects.add(Vec4i(t.z, r.y, r.z, r.w));
            if (t.w < r.w) maxRects.add(Vec4i(r.x, t.w, r.z, r.w));
        }

        // Remove duplicates.

        for (int i = maxRects.getSize() - 1; i >= 0; i--)
        {
            const Vec4i& a = maxRects[i];
            for (int j = 0; j < maxRects.getSize(); j++)
            {
                const Vec4i& b = maxRects[j];
                if (i != j && a.x >= b.x && a.y >= b.y && a.z <= b.z && a.w <= b.w)
                {
                    maxRects.removeSwap(i);
                    break;
                }
            }
        }
    }

    // Determine final size.

    m_atlasSize = 1;
    for (int i = 0; i < m_items.getSize(); i++)
        m_atlasSize = max(m_atlasSize, m_items[i].pos + m_items[i].size);
}

//------------------------------------------------------------------------

void TextureAtlas::createAtlas(void)
{
    Image* image = new Image(m_atlasSize, m_format);
    m_atlasTexture = Texture(image);
    image->clear();

    for (int i = 0; i < m_items.getSize(); i++)
    {
        const Item& item = m_items[i];
        Vec2i pos = item.pos + item.border;
        Vec2i size = item.size - item.border * 2;
        Vec2i wrap = (item.wrap) ? size - 1 : 0;

        image->set(pos, *item.texture.getImage(), 0, size);
        for (int j = 0; j < item.border; j++)
        {
            image->set(pos + Vec2i(-1, 0), *image, pos + Vec2i(wrap.x, 0), Vec2i(1, size.y));
            image->set(pos + Vec2i(size.x, 0), *image, pos + Vec2i(size.x - 1 - wrap.x, 0), Vec2i(1, size.y));
            image->set(pos + Vec2i(-1, -1), *image, pos + Vec2i(-1, wrap.y), Vec2i(size.x + 2, 1));
            image->set(pos + Vec2i(-1, size.y), *image, pos + Vec2i(-1, size.y - 1 - wrap.y), Vec2i(size.x + 2, 1));
            pos -= 1;
            size += 2;
        }
    }
}

//------------------------------------------------------------------------

int TextureAtlas::compareVec2i(void* data, int idxA, int idxB)
{
    const Vec2i& a = ((const Vec2i*)data)[idxA];
    const Vec2i& b = ((const Vec2i*)data)[idxB];
    return (a.x < b.x) ? -1 : (a.x > b.x) ? 1 : (a.y < b.y) ? -1 : (a.y > b.y) ? 1 : 0;
}

//------------------------------------------------------------------------

void TextureAtlas::swapVec2i(void* data, int idxA, int idxB)
{
    Vec2i& a = ((Vec2i*)data)[idxA];
    Vec2i& b = ((Vec2i*)data)[idxB];
    swap(a, b);
}

//------------------------------------------------------------------------