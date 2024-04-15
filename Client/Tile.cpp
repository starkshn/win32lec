#include "pch.h"
#include "Tile.h"
#include "Texture.h"

int32 Tile::g_tileObjectID = 0;

Tile::Tile()
{
    // 고유한 Tile 오브젝트 ID
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
    // 타일의 경우 전체 타일 텍스쳐를 로드한다음
    // 원하는 인덱스의 타일을 출력하기 위해 부모 Render호출하지 않는다.
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

    // 중요한 개념
    // 코테에도 나온다.
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
