#include "Level.h"
#include "TileLayer.h"

using namespace std;

Level::Level(vector<Tileset> tilesets, vector<Layer *> layers) {
	this->tilesets = tilesets;
	this->layers = layers;
}

Level::~Level() {
	tilesets.clear();
	layers.clear();
}

void Level::Update() {
	for each (Layer * ly in layers) {
		ly->Update();
	}
}

void Level::Render() {
	for each (Layer * ly in layers) {
		ly->Render();
	}
}

vector<Tileset> * Level::getTilesets() {
	return &this->tilesets;
}

vector<Layer *> * Level::getLayers() {
	return &this->layers;
}

vector<TileLayer *> * Level::getCollidableTileLayers() {
	vector<TileLayer *> * colliders = new vector<TileLayer *>();
	for each (Layer * layer in layers) {
		if (TileLayer * tl = dynamic_cast<TileLayer *>(layer)) {
			if (tl->IsCollidable()) {
				colliders->push_back(tl);
			}
		}
	}
	return colliders;
}