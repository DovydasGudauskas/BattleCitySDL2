void InitializeMap(SDL_Texture* TilesetPtr, double scale_x, double scale_y);
void LoadMap(int Level);
void RenderMap(SDL_Renderer* Renderer);
void DrawMapBackground(SDL_Renderer* Renderer);
void* GetMapTiles();
void RemoveMapTile(int tileID);