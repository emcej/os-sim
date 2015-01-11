#include "MemoryManager.h"

unsigned char PageTable::getFrameNumber(unsigned char pageNumber) //zwr�� numer ramki w kt�rej jest szukana strona, je�li nie ma w ramie wy�lij za du�� liczb�
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
	throw (std::string)"Fatal error! Memory full!";                      // je�li nie znajdzie wolnego numeru strony to ca�a pami�� si� wysypie
}
//-----------------------------------------------------------------------------------------------------------------------------------------//

// wydaje mi si�, �e takow� funkcj� to powinien dostarczy� mi dysk
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

	_fifoList.push_back(_pageTable.getFrameNumber(pageNumber));           // skoro strona znowu b�dzie znajdowa� si� w ramie to dodaj� j� do listy przysz�ych ofiar 
	memoryIndicator[_pageTable.getFrameNumber(pageNumber)] = 1;
}
unsigned char MemoryManager::takeVictim()    // zrzuca stronice na dysk wed�ug algorytmu fifo, zwraca numer ramki, kt�ra mo�e by� teraz zapisana
{
	unsigned char frame =  _fifoList.front();
	saveOnDisc(_pageTable.getPageNumber(frame));	// ta funkcja jeszcze nie dzia�a
	_fifoList.erase(_fifoList.begin());

	return frame;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MemoryManager::MemoryManager()
{

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
		// znajduje ramk� na dane itd, celowo pomijam memoryIndicator poniewa� ta ramka i tak by�a zaj�ta
		unsigned char frame = findFreeMemory();
		_pageTable.setPageLocation(page, frame);
		_fifoList.push_back(frame);
		

		//++++++++++++++ tutaj potrzebna jest funkcja przepisuj�ca ramki z dysku na RAM
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
		
		//++++++++++++++++funkcja wysy�aj�ca do dysku rozkaz usuni�cia tej ramki, bo i tak tylko bym j� nadpisa�
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
	return page;
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

/*			TO DO LIST:
			-	ogarnij adresacj� stron na dysku
										*/	