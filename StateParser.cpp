#include "StateParser.h"
#include "TextureManager.h"
#include "EntityFactory.h"
#include "AllEntities.hpp"

void StateParser::parseObjects(XMLElement * stateRoot, vector<Entity*>* entities)
{
	string type = stateRoot->Attribute("type");
	string id = stateRoot->Attribute("texture");

	int x = atoi(stateRoot->Attribute("x"));
	int y = atoi(stateRoot->Attribute("y"));
	int width = atoi(stateRoot->Attribute("width"));
	int height = atoi(stateRoot->Attribute("height"));
	int numFrames = atoi(stateRoot->Attribute("numFrames"));
	int row = atoi(stateRoot->Attribute("row"));

	Entity * ent = EntityCreator->CreateEntity(type);
	if (dynamic_cast<Button *>(ent))
	{
		int callback = atoi(stateRoot->Attribute("callback"));
		x = (Tools::GetWidth() / 2) - (width / 2);
		if (callback != 0)
			dynamic_cast<Button *>(ent)->CallbackID = callback;
	}

	if (Enemy * enemy = dynamic_cast<Enemy *>(ent))
	{
		int enemyType = atoi(stateRoot->Attribute("enemy"));
		enemy->SetType(enemyType);
	}
	if (Player * pl = dynamic_cast<Player *>(ent))
	{
		float jump = (float)atof(stateRoot->Attribute("jump"));
		pl->SetJump(jump);
	}
	EntityParams * params = new EntityParams(id.c_str(), x, y, width, height, numFrames, row);
	ent->Load(params);
	entities->push_back(ent);
}

void StateParser::parseTextures(XMLElement * stateRoot, vector<string>* textures)
{
	string file = stateRoot->Attribute("file");
	string id = stateRoot->Attribute("ID");
	Manager->Load(file.c_str(), id.c_str());
	textures->push_back(id);
}

bool StateParser::ParseState(const char * stateFile, string stateID, vector<Entity*>* entitats, vector<string>* textures)
{
	XMLDocument doc;
	string path = PATH;
	path.append(stateFile);
	
	doc.LoadFile(path.c_str());
	
	if (doc.Error())
	{
		cout << doc.ErrorName() << endl;
		return false;
	}

	XMLElement * state = doc.FirstChildElement("state");
	XMLElement * tex = state->FirstChildElement("textures");
	for (auto e = tex->FirstChildElement("texture"); 
	e != NULL; e = e->NextSiblingElement("texture"))
	{
		parseTextures(e, textures);
	}

	XMLElement * obj = state->FirstChildElement("objects");
	for (auto e = obj->FirstChildElement("object");
	e != NULL; e = e->NextSiblingElement("object"))
	{
		parseObjects(e, entitats);
	}
	return true;
}
