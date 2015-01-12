#include "MemoryManager.h"

char PageTable::getFrameNumber(char pageNumber) //zwr�� numer ramki w kt�rej jest szukana strona, je�li nie ma w ramie wy�lij za du�� liczb�
{
	for (auto iter = _content.begin(); iter != _content.end(); iter++)
	{
		if (iter->first == pageNumber)
			return iter->second;
	}
	return -1;
}
char PageTable::getPageNumber(char frameNumber)
{
	for (auto iter = _content.begin(); iter != _content.end(); iter++)
	{
		if (iter->second == frameNumber)
			return iter->first;
	}
	return -1;
}
void PageTable::setPageLocation(char pageNumber, char location)
{
	for (auto iter = _content.begin(); iter != _content.end(); iter++)
	{
		if (iter->first == pageNumber)
			iter->second = location;
	}
}

void MemoryManager::RAMzero()
{
	for (int i = 0; i<16 ; ++i)
	for (int j = 0 ; j <16 ; ++j)
		RAM[i][j] = 0;
}

char MemoryManager::findFreeMemory()
{
	for (char i = 0; i < 16; i++)
	{
		if (!memoryIndicator[i])
			return i;
	}
	return takeVictim();
}
char MemoryManager::findFreePage()
{
	for (char i = 0; i < 256; i++)
	{
		if (!pageIndicator[i])				
			return i;          
	}
	throw (std::string)"Fatal error! Memory full!";                      // je�li nie znajdzie wolnego numeru strony to ca�a pami�� si� wysypie
}
//-----------------------------------------------------------------------------------------------------------------------------------------//

// wydaje mi si�, �e takow� funkcj� to powinien dostarczy� mi dysk
void MemoryManager::saveOnDisc(char pageNumber)      
{
	// DISK ADDRESS
	int addr;
	for (addr = 0x10; addr < 0x7E; ++addr)
		if (!memoryIndicator[addr])
			break;
	short location = (addr - 0x10) * 0x10;

	for (int i = 0x00; i < 0x10; ++i)
	{
		driveManager->saveToSwap(RAM[_pageTable.getFrameNumber(pageNumber)][i], location + i);
		RAM[_pageTable.getFrameNumber(pageNumber)][i] = 0x00;
	}
		
	char x = _pageTable.getFrameNumber(pageNumber);
	memoryIndicator[x] = 0;
	memoryIndicator[addr] = 1;
	_pageTable.setPageLocation(pageNumber, addr);    // NUMERY RAMEK NA DYSKU 16+
}
char MemoryManager::getFromDisc(char pageNumber)
{
	char frame = _pageTable.getFrameNumber(pageNumber);
	short offset = ((short)frame - 0x10) * 0x10;

	char victimFrame = takeVictim();

	for (int i = 0; i < 0x10; ++i)
		RAM[victimFrame][i] = driveManager->readFromSwap(offset + i);
	_pageTable.setPageLocation(pageNumber, victimFrame);
	
	memoryIndicator[frame] = 0;
	return victimFrame;
}
char MemoryManager::takeVictim()    // zrzuca stronice na dysk wed�ug algorytmu fifo, zwraca numer ramki, kt�ra mo�e by� teraz zapisana
{
	char frame =  _fifoList.front();
	saveOnDisc(_pageTable.getPageNumber(frame));
	_fifoList.erase(_fifoList.begin());

	return frame;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryManager::MemoryManager(DriveManager* driveManager)
	: driveManager(driveManager)
{
	//RAMzero();
}
MemoryManager::~MemoryManager()
{

}

char MemoryManager::readData(short address)    // NIEDOROBIONE 
{
	char page = char((address & 0x0ff0) >> 4);
	char offset = char(address & 0x000f);

	if (_pageTable.getFrameNumber(page) < 16)
		return RAM[_pageTable.getFrameNumber(page)][offset];
	else
	{
		// znajduje ramk� na dane itd, celowo pomijam memoryIndicator poniewa� ta ramka i tak by�a zaj�ta
		char frame = findFreeMemory();
		_pageTable.setPageLocation(page, frame);
		_fifoList.push_back(frame);
		

		//++++++++++++++ tutaj potrzebna jest funkcja przepisuj�ca ramki z dysku na RAM
		return RAM[frame][offset];
	}
}
void MemoryManager::saveData(char data, short address)
{
	char page = char((address & 0x0ff0) >> 4);
	char offset = char(address & 0x000f);
	
	if (_pageTable.getFrameNumber(page) < 16)
		RAM[_pageTable.getFrameNumber(page)][offset] = data;
	else
		RAM[getFromDisc(page)][offset] = data;
}

short MemoryManager::allocateMemory()
{
	char page = findFreePage();
	char frame = findFreeMemory();
	_pageTable._content.push_back(std::pair<char, char>(page, frame));
	_fifoList.push_back(frame);
	memoryIndicator[frame] = 1;
	pageIndicator[page] = 1;
	
	short address = (short)page << 4;
	return address;
}
void MemoryManager::freeMemory(char pageNumber)
{
	for (auto i = _pageTable._content.begin(); i != _pageTable._content.end();)
	{
		if (i->first == pageNumber)
		{
			_fifoList.erase(std::find(_fifoList.begin(), _fifoList.end(), i->second));
			memoryIndicator[i->second] = 0;
			pageIndicator[i->first] = 0;
			i = _pageTable._content.erase(i);
		}
		else
			i++;
	}
}

void MemoryManager::printRAM()
{

	std::cout << "offset:";
	for (int i = 0; i < 16; ++i)
	{
		std::cout.width(4);
		std::cout  << i;
	}
	std::cout << std::endl;

	std::cout << " frame:  ---------------------------------------------------------------" << std::endl;
	
	for (int i = 0; i < 16; ++i)
	{	
		std::cout.width(6);
		std::cout << std::dec << i << "|";
		for (int j = 0; j < 16; ++j)
		{
			std::cout.width(4);
			std::cout << std::hex << (int)RAM[i][j];
		}
		std::cout << std::endl;
	}
		
}
void MemoryManager::printPageTable()
{
	std::cout << " PageTable:" << std::endl;
	std::cout << " Page | Frame" << std::endl;
	//std::vector<std::pair<char, char>>::iterator i;
	for (auto i : _pageTable._content)
	{
		std::cout.width(5);
		std::cout << std::dec << (int)i.first;
		std::cout << " | " ;
		std::cout.width(3);
		std::cout << std::dec << (int)i.second << std::endl;
	}

}
void MemoryManager::printFifoList()
{
	std::cout << "Frames numbers in Fifo list: \n  FRONT "<< std::endl;
	for (auto i : _fifoList)
	{
		std::cout.width(5);
		std::cout <<std::internal << std::dec << (int)i << std::endl;
	}
	std::cout << "  BACK" << std::endl;
}

/*			TO DO LIST:
			-	ogarnij adresacj� stron na dysku
										*/	