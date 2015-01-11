#include "MemoryManager.h"

unsigned char PageTable::getFrameNumber(unsigned char pageNumber) //zwróæ numer ramki w której jest szukana strona, jeœli nie ma w ramie wyœlij za du¿¹ liczbê
{
	for (auto iter = _content.begin(); iter != _content.end(); iter++)
	{
		if (iter->first == pageNumber)
			return iter->second;
	}
	return(255);
}
unsigned char PageTable::getPageNumber(unsigned char frameNumber)
{
	for (auto iter = _content.begin(); iter != _content.end(); iter++)
	{
		if (iter->second == frameNumber)
			return iter->first;
	}
	return 255;
}
void PageTable::setPageLocation(unsigned char pageNumber, char location)
{
	for (auto iter = _content.begin(); iter != _content.end(); iter++)
	{
		if (iter->first == pageNumber)
			iter->second = location;
	}
}

<<<<<<< HEAD
void MemoryManager::RAMzero()
{
	for (int i = 0; i<16 ; ++i)
	for (int j = 0 ; j <16 ; ++j)
		RAM[i][j] = 0;
}
=======
>>>>>>> 9c59a0f79e361b84105be96ef9a4cc148f474e2d

unsigned char MemoryManager::findFreeMemory()
{
	for (unsigned char i = 0; i < 16; i++)
	{
		if (!memoryIndicator[i])
			return i;
	}
	return takeVictim();
}
unsigned char MemoryManager::findFreePage()
{
	for (unsigned char i = 0; i < 256; i++)
	{
		if (!pageIndicator[i])				
			return i;          
	}
	throw (std::string)"Fatal error! Memory full!";                      // jeœli nie znajdzie wolnego numeru strony to ca³a pamiêæ siê wysypie
}
//-----------------------------------------------------------------------------------------------------------------------------------------//

// wydaje mi siê, ¿e takow¹ funkcjê to powinien dostarczyæ mi dysk
void MemoryManager::saveOnDisc(unsigned char pageNumber)      
{
	for (auto iter = _fifoList.begin(); iter != _fifoList.end(); iter++)
	{
		if (*iter == pageNumber)
			_fifoList.erase(iter);
	}
	// tutaj funkcja zapisu na dysk
	memoryIndicator[_pageTable.getFrameNumber(pageNumber)] = 0;
	_pageTable.setPageLocation(pageNumber, 16);    // NUMERY RAMEK NA DYSKU 16+
}
void MemoryManager::getFromDisc(unsigned char pageNumber)
{

	_fifoList.push_back(_pageTable.getFrameNumber(pageNumber));           // skoro strona znowu bêdzie znajdowaæ siê w ramie to dodajê j¹ do listy przysz³ych ofiar 
	memoryIndicator[_pageTable.getFrameNumber(pageNumber)] = 1;
}
unsigned char MemoryManager::takeVictim()    // zrzuca stronice na dysk wed³ug algorytmu fifo, zwraca numer ramki, która mo¿e byæ teraz zapisana
{
	unsigned char frame =  _fifoList.front();
	saveOnDisc(_pageTable.getPageNumber(frame));	// ta funkcja jeszcze nie dzia³a
	_fifoList.erase(_fifoList.begin());

	return frame;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryManager::MemoryManager()
{
<<<<<<< HEAD
	//RAMzero();
=======

>>>>>>> 9c59a0f79e361b84105be96ef9a4cc148f474e2d
}
MemoryManager::~MemoryManager()
{

}

unsigned char MemoryManager::readData(short address)    // NIEDOROBIONE 
{
	unsigned char page = unsigned char((address & 0x0ff0) >> 4);
	unsigned char offset = unsigned char(address & 0x000f);

	if (_pageTable.getFrameNumber(page) < 16)
		return RAM[_pageTable.getFrameNumber(page)][offset];
	else
	{
		// znajduje ramkê na dane itd, celowo pomijam memoryIndicator poniewa¿ ta ramka i tak by³a zajêta
		unsigned char frame = findFreeMemory();
		_pageTable.setPageLocation(page, frame);
		_fifoList.push_back(frame);
		

		//++++++++++++++ tutaj potrzebna jest funkcja przepisuj¹ca ramki z dysku na RAM
		return RAM[frame][offset];
	}
}
void MemoryManager::saveData(unsigned char data, short address)
{
	unsigned char page = unsigned char((address & 0x0ff0) >> 4);
	unsigned char offset = unsigned char(address & 0x000f);
	
	if (_pageTable.getFrameNumber(page) < 16)
		RAM[_pageTable.getFrameNumber(page)][offset] = data;
	else
	{
		
		//++++++++++++++++funkcja wysy³aj¹ca do dysku rozkaz usuniêcia tej ramki, bo i tak tylko bym j¹ nadpisa³
		unsigned char frame = findFreeMemory();
		_pageTable.setPageLocation(page, frame);
		_fifoList.push_back(frame);
		
		RAM[frame][offset] = data;
	}
}

unsigned char MemoryManager::allocateMemory()
{
	unsigned char page = findFreePage();
	unsigned char frame = findFreeMemory();
	_pageTable._content.push_back(std::pair<char, char>(page, frame));
	_fifoList.push_back(frame);
	memoryIndicator[frame] = 1;
	pageIndicator[page] = 1;
<<<<<<< HEAD
	
	short address = page << 4;
	return address;
=======
	return page;
>>>>>>> 9c59a0f79e361b84105be96ef9a4cc148f474e2d
}
void MemoryManager::freeMemory(unsigned char pageNumber)
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

<<<<<<< HEAD
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
	//std::vector<std::pair<unsigned char, unsigned char>>::iterator i;
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

=======
>>>>>>> 9c59a0f79e361b84105be96ef9a4cc148f474e2d
/*			TO DO LIST:
			-	ogarnij adresacjê stron na dysku
										*/	