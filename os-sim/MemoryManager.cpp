#include "MemoryManager.h"
// freeMemory() NIE DZIA£A

char PageTable::getFrameNumber(char pageNumber) 
{
	for(std::vector<std::pair<char, char>>::iterator iter = _content.begin(); iter != _content.end(); ++iter)
	{
		if (iter->first == pageNumber)
			return iter->second;
	}
	return -1;
}
char PageTable::getPageNumber(char frameNumber)
{
	for(std::vector<std::pair<char, char>>::iterator iter = _content.begin(); iter != _content.end(); ++iter)
	{
		if (iter->second == frameNumber)
			return iter->first;
	}
	return -1;
}
void PageTable::setPageLocation(char pageNumber, char location)
{
	//for (auto iter : _content)     // dlaczego nie dzia³a tutaj to auto???????
	for (std::vector<std::pair<char,char>>::iterator iter = _content.begin() ; iter != _content.end() ; ++iter)    
	{
		if (iter->first == pageNumber)
		{
			iter->second = location;
			return;
		}
	}
	//_content.push_back(std::pair<char,char>(pageNumber,location)); //  nie jestem tego pewny
}
void PageTable::printPageTable()
{
	std::cout << " PageTable:" << std::endl;
	std::cout << " Page | Frame" << std::endl;
	//std::vector<std::pair<char, char>>::iterator i;
	for (auto i : _content)
	{
		std::cout.width(5);
		std::cout << std::dec << (int)i.first;
		std::cout << " | ";
		std::cout.width(3);
		std::cout << std::dec << (int)i.second << std::endl;
	}
}

void MemoryManager::RAMzero()
{
	for (int i = 0; i < FRAME_NUMBER; ++i)
	for (int j = 0; j < FRAME_SIZE  ; ++j)
		RAM[i][j] = 0;
}

char MemoryManager::findFreeMemory()
{
	for (char i = 0; i < FRAME_NUMBER; ++i)
	{
		if (!memoryIndicator[i])
			return i;
	}
	return takeVictim();
}
char MemoryManager::findFreePage()
{
	for (char i = 0; i < MAX_ADDRESS; i++)
	{
		if (!pageIndicator[i])
		{
			return i;          
		}
	}
	throw (std::string)"Fatal error! Memory full!";
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
void MemoryManager::saveOnDisc(char pageNumber)      
{
	char frameNumber = _pageTable.getFrameNumber(pageNumber);

	// DISK ADDRESS
	int addr;
	// u¿ywania tych FRAME_NUMBERÓW i SIZEÓW nie jestem pewien
	for( addr = FRAME_NUMBER; addr < 0x7E; ++addr)
		if (!memoryIndicator[addr])
			break;
	short location = (addr - FRAME_NUMBER) * FRAME_SIZE;
	
	for (int i = 0; i < FRAME_SIZE; ++i)
	{
		driveManager->saveToSwap(RAM[frameNumber][i], location + i);
		RAM[frameNumber][i] = 0;
	}
		
	memoryIndicator[frameNumber] = 0;
	memoryIndicator[addr] = 1;
	_pageTable.setPageLocation(pageNumber, addr);    // NUMERY RAMEK NA DYSKU FRAME_NUMBER +
}
char MemoryManager::getFromDisc(char pageNumber)
{
	char frame = _pageTable.getFrameNumber(pageNumber);
	short offset = ((short)frame - FRAME_NUMBER) * FRAME_SIZE;

	char victimFrame = takeVictim();

	for (int i = 0; i < FRAME_SIZE; ++i)
		RAM[victimFrame][i] = driveManager->readFromSwap(offset + i);
	_pageTable.setPageLocation(pageNumber, victimFrame);
	
	_fifoList.push_back(victimFrame);
	memoryIndicator[frame] = 0;
	return victimFrame;
}
char MemoryManager::takeVictim()    // zrzuca stronice na dysk wed³ug algorytmu fifo, zwraca numer ramki, która mo¿e byæ teraz zapisana
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

char MemoryManager::readData(short address) 
{
	char page = char((address & 0x0ff0) >> 4);
	char offset = char(address & 0x000f);
	char frame = _pageTable.getFrameNumber(page);
	 
	if (frame < FRAME_NUMBER)
		return RAM[frame][offset];
	else
	{
		// znajduje ramkê na dane itd, celowo pomijam memoryIndicator poniewa¿ ta ramka i tak by³a zajêta
		frame = findFreeMemory();
		_pageTable.setPageLocation(page, frame);
		_fifoList.push_back(frame);
		

		//++++++++++++++ tutaj potrzebna jest funkcja przepisuj¹ca ramki z dysku na RAM
		return RAM[frame][offset];
	}
}
void MemoryManager::saveData(char data, short address)
{
	char page = char((address & 0x0ff0) >> 4);
	char offset = char(address & 0x000f);
	
	char frameNumber = _pageTable.getFrameNumber(page);
	if (frameNumber < FRAME_NUMBER)
		RAM[frameNumber][offset] = data;
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
	
	/*short address = (short)page << 4;
	return address;*/
	return((short)page << 4);
}
void MemoryManager::freeMemory(char pageNumber)
{
	for (auto iter = _pageTable._content.begin(); iter != _pageTable._content.end(); ++iter)
	{
		if (iter->first == pageNumber)
		{
			if (iter->second < FRAME_NUMBER)
			{
				_fifoList.erase(std::find(_fifoList.begin(), _fifoList.end(), iter->second));
				memoryIndicator[iter->second] = 0;
				pageIndicator[iter->first] = 0;
				iter = _pageTable._content.erase(iter);
				return;
			}
			else
			{
				memoryIndicator[iter->second] = 0;
				pageIndicator[iter->first] = 0;
				iter = _pageTable._content.erase(iter);
				return;
			}
		}
	}
}

void MemoryManager::printRAM()
{

	std::cout << "offset:";
	for (int i = 0; i < FRAME_SIZE; ++i)
	{
		std::cout.width(4);
		std::cout<< std::uppercase << std::hex  << i;
	}
	std::cout << std::endl;

	std::cout << " frame:  ";
	for (int i = 0 ; i < FRAME_SIZE; ++i)
	std::cout <<"----";
	std::cout << std::endl;
	
	for (int i = 0; i < FRAME_NUMBER; ++i)
	{	
		std::cout.width(6);
		std::cout << std::uppercase  << std::hex << i << "|";
		for (int j = 0; j < FRAME_SIZE; ++j)
		{
			std::cout.width(4);
			std::cout << std::uppercase << std::hex << (int)RAM[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
		
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
	std::cout << std::endl;
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
	std::cout << std::endl;
}