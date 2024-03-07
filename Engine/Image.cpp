//https://flylib.com/books/en/1.143.1.23/1/ 
#include "Image.h"

Image::Image(std::string fileName) {
	m_sFilename = fileName;
	Load();
}

void Image::Load() {/* try {
	m_info = new ImageInformation();
	m_info = TextureLoader.ImageInformationFromFile(m_sFilename);
	m_image = TextureLoader.FromFile(CGameEngine.Device3D, m_sFilename); } 
catch (DirectXException d3de) { Console.AddLine("Unable to load image" + m_sFilename);
Console.AddLine(d3de.ErrorString); } catch (Exception e) { Console.AddLine("Unable to load image" + m_sFilename);        Console.AddLine(e.Message); } */}