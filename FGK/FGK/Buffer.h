#pragma once
class Buffer
{
private:
	int w;
	int h;
	int size;
	
public:
	unsigned int* color;

	Buffer();
	Buffer(int width, int height);

	void SetSize(int width, int height);
	void ClearColor(unsigned int pickedColor);
	bool Save();

	int GetWidth();
	int GetHeight();
};

