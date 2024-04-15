#include "pch.h"
#include "Tile.h"
#include "Texture.h"

int32 Tile::g_tileObjectID = 0;

Tile::Tile()
{
    // ������ Tile ������Ʈ ID
    SetTileID(g_tileObjectID++);
}

Tile::~Tile()
{

}

Tile* Tile::Clone()
{
    return nullptr;
}

void Tile::Update()
{

}

void Tile::Render()
{
    // Ÿ���� ��� ��ü Ÿ�� �ؽ��ĸ� �ε��Ѵ���
    // ���ϴ� �ε����� Ÿ���� ����ϱ� ���� �θ� Renderȣ������ �ʴ´�.
    // GameObject::Render();

    if (nullptr == GetTexture() || -1 == _tileIdx)
        return;

    SetRenderPos(CAMERA->GetRenderPos(GetPos()));
    ComponentRender();

    Vec2 renderPos = GetRenderPos();
    renderPos += GetOffSet();
    Vec2 scale = GetScale();
    
    uint32 texWidth = GetTexture()->GetTexWidth();
    uint32 texHeight = GetTexture()->GetTexHeight();

    uint32 maxCol = texWidth / TILE_SIZE;
    uint32 maxRow = texHeight / TILE_SIZE;

    // �߿��� ����
    // ���׿��� ���´�.
    uint32 curRow = (uint32)(_tileIdx / maxRow);
    uint32 curCol = (uint32)(_tileIdx % maxCol);

    assert(maxRow >= curRow);

    TransparentBlt
    (
        GET_MEMDC,
        int(renderPos.x - scale.x / 2), 
        int(renderPos.y - scale.y / 2), 
        TILE_SIZE,
        TILE_SIZE,
        GetTexture()->GetDC(),
        curCol * TILE_SIZE,
        curRow * TILE_SIZE,
        TILE_SIZE, TILE_SIZE,
        RGB(255, 0, 255)
    );
}

void Tile::Init()
{
    // TODO...
    // _tileIdx = 0;
}

void Tile::Begin()
{
    Object::Begin();
}

void Tile::End()
{
    Object::End();
}
