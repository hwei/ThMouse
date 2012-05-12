#include "stdafx.h"
#include "ReadConfig.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


BOOL readGamesFile(GameConfigArray * pConfig)
{
	ifstream gamesFile("games");
	if(!gamesFile)
	{
		MessageBox( NULL, "Can not find games file.", "Launcher", MB_OK );
		return 0;
	}
	int configNum;
	for(configNum=0; configNum<GAME_CONFIG_MAX_LEN && !gamesFile.eof(); configNum++)
	{
		string line, block;
		getline(gamesFile, line);
		if(line.empty())
		{
			configNum--;
			continue;
		}
		if(line[0] == ';')
		{
			configNum--;
			continue;
		}
		stringstream split;
		split<<line;
		split>>block;
		strcpy(pConfig->Configs[configNum].ProcessName, block.c_str());
		split>>block;
		stringstream convert;
		string::size_type stringIndex1 = 0, stringIndex2 = -1;
		int addNum;
		DWORD address;
		string numStr;
		for(addNum=0; addNum<ADDRESS_CHAIN_MAX_LEN; addNum++)
		{
			stringIndex1 = block.find('[', stringIndex2+1);
			if(stringIndex1 == string::npos)
			{
				break;
			}
			stringIndex2 = block.find(']', stringIndex1+1);
			if(stringIndex2 == string::npos)
			{
				break;
			}
			numStr = block.substr(stringIndex1 + 1, stringIndex2 - stringIndex1 - 1);
			convert.clear();
			convert<<numStr;
			convert>>hex>>address;
			pConfig->Configs[configNum].Posistion.Chain[addNum] = address;
		}
		if(addNum == 0)
		{
			configNum--;
			continue;
		}
		pConfig->Configs[configNum].Posistion.Length = addNum;
		split>>block;
		if(block.compare("int") == 0)
			pConfig->Configs[configNum].PosDataType = Int_DataType;
		else if(block.compare("float") == 0)
			pConfig->Configs[configNum].PosDataType = Float_DataType;
		else
		{
			configNum--;
			continue;
		}
		split>>block;
		float pixelRate;
		convert.clear();
		convert<<block;
		convert>>pixelRate;
		pConfig->Configs[configNum].PixelRate = pixelRate;
		split>>block;
		if(block[0] != '(' || block[block.length()-1] != ')')
		{
			configNum--;
			continue;
		}
		stringIndex1 = block.find(',');
		if(stringIndex1 == string::npos)
		{
			configNum--;
			continue;
		}
		numStr = block.substr(1, stringIndex1 - 1);
		float offsetX, offsetY;
		convert.clear();
		convert<<numStr;
		convert>>offsetX;
		pConfig->Configs[configNum].PixelOffset.X = offsetX;
		numStr = block.substr(stringIndex1 + 1, block.length() - stringIndex1 - 2);
		convert.clear();
		convert<<numStr;
		convert>>offsetY;
		pConfig->Configs[configNum].PixelOffset.Y = offsetY;
	}
	
	if(configNum == 0)
	{
		MessageBox( NULL, "No valid data in config file.", "Launcher", MB_OK );
		return 0;
	}
	pConfig->Length = configNum;

	return 1;
}

BOOL readIniFile(int * pLeftButton, char * pTextureFilePath)
{
	ifstream iniFile("ThMouse.ini");
	if(!iniFile)
	{
		MessageBox( NULL, "Can not find ThMouse.ini file.", "Launcher", MB_OK );
		return 0;
	}
	string line;
	getline(iniFile, line);
	if(line.compare("[ThMouse]") != 0)
	{
		MessageBox( NULL, "ThMouse.ini file error.", "Launcher", MB_OK );
		return 0;
	}
	while(!iniFile.eof())
	{
		getline(iniFile, line);
		if(line.find("LeftButton") != string::npos)
		{
			string::size_type eqIndex = line.find('=');
			string numStr = line.substr(eqIndex+1);
			stringstream ss;
			ss<<numStr;
			ss>>*pLeftButton;
		}
		else if(line.find("CursorTexture") != string::npos)
		{
			string::size_type eqIndex = line.find('=');
			string pathStr = line.substr(eqIndex+1);
			stringstream ss;
			ss<<pathStr;
			ss>>pTextureFilePath;
		}
	}
	return 1;
}
