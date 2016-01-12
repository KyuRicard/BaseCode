#include "LayerParser.h"
#include "Loaders.h"
#include "Tools.h"

using namespace std;
using namespace tinyxml2;

LayerParser * LayerParser::instance = 0;

void LayerParser::ParseTileset(XMLElement * element, Tileset * tileset)
{
	tileset->firstGridID = element->IntAttribute("firstgid");
	tileset->margin = element->IntAttribute("margin");
	tileset->name = element->Attribute("name");
	tileset->spacing = element->IntAttribute("spacing");
	tileset->tileHeight = element->IntAttribute("tileheight");
	tileset->tileWidth = element->IntAttribute("tilewidth");
	tileset->spacing = element->IntAttribute("spaing");
	string file = element->FirstChildElement("image")->Attribute("source");
	tileset->numColumns = element->FirstChildElement("image")->IntAttribute("width") / (tileset->tileWidth + tileset->spacing);
	Manager->Load(file.c_str(), tileset->name);
}

TileLayer * LayerParser::ParseTileLayer(string file)
{
	vector<Tileset> tilesets;
	XMLDocument doc;
	doc.LoadFile(file.c_str());
	if (doc.Error())
	{
		cout << doc.ErrorName() << endl;
		return NULL;
	}

	XMLElement * map = doc.FirstChildElement("map");
	for (auto e = map->FirstChildElement("tileset"); e != NULL;
	e = e->NextSiblingElement("tileset")) {
		Tileset ts;
		ParseTileset(e, &ts);
		tilesets.push_back(ts);
	}

	XMLElement * layer = map->FirstChildElement("layer");
	string data = layer->FirstChildElement("data")->FirstChild()->ToText()->Value();
	int width = layer->IntAttribute("width");
	int height = layer->IntAttribute("height");
	int tilewidth = map->IntAttribute("tilewidth");
	int tileheight = map->IntAttribute("tileheight");
	vector<vector<int>> tiles = ParseData(data, width, height);
	TileLayer * tl = new TileLayer(width, height, tilewidth, tileheight, tilesets);
	tl->SetTileIDs(tiles);
	return tl;
}

vector<vector<int>> LayerParser::ParseData(string data, int width, int height)
{
	vector<vector<int>> layer;
	data = Tools::Clear(data);
	string text = base64_decode(data);

	uLongf size = width * height * sizeof(int);
	vector<int> ids(size);
	uncompress((Bytef *)&ids[0], &size, (const Bytef *)text.c_str(), text.size());
	for (int row = 0; row < height; row++)
	{
		vector<int> fila;
		for (int col = 0; col < width; col++)
		{
			fila.push_back(ids[row * width + col]);
		}
		layer.push_back(fila);
	}
	return layer;
}
