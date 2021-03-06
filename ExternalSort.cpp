#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;

const size_t max_length = 256;
const size_t size_buffer = 512 * 1024 / max_length;


void read_data(size_t size_buffer, vector<string> &res, ifstream &in)
{
	for (size_t i = 0; i < size_buffer; ++i)
	{
		string s;
		if (getline(in, s))
		{
			res.push_back(s);
		}
		else
		{
			break;
		}
	}
}

void merge(vector<string> &block1, vector<string> &block2, vector<string> &mergeBlock)
{
	int ind1, ind2;
	ind1 = ind2 = 0;
	while (ind1 < block1.size() || ind2 < block2.size())
	{
		if (ind1 == block1.size())
		{
			mergeBlock.push_back(block2[ind2]);
			++ind2;
		}
		else
		{
			if (ind2 == block2.size())
			{
				mergeBlock.push_back(block1[ind1]);
				++ind1;
			}
			else
			{
				if (block1[ind1] < block2[ind2])
				{
					mergeBlock.push_back(block1[ind1]);
					++ind1;
				}
				else
				{
					mergeBlock.push_back(block2[ind2]);
					++ind2;
				}
			}
		}
	}
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Usage: ExternalSort.exe SortFileName.txt Result.txt";
		return 0;
	}
	
	int countChunk = 0;

	//сортируем блоки
	ifstream in(argv[1]);
	ofstream out("special.txt");
	while (true)
	{
		vector<string> chunk;
		read_data(size_buffer, chunk, in);
		sort(chunk.begin(), chunk.end());
		for (int j = 0; j < chunk.size(); ++j)
		{
			out << chunk[j] << '\n';
		}		

		if (chunk.size() == 0)
		{
			break;
		}

		++countChunk;
	}	
	in.close();
	out.close();

	ofstream ans(argv[2]);

	string name1 = "special.txt";
	string name2 = "chunks.txt";

	//сортируем слиянием блоков
	for (int i = 0; i < countChunk; ++i)
	{					
		ifstream data(name1);
		ofstream newData(name2);
		vector<string> block1;
		read_data(size_buffer, block1, data);

		for (int j = i + 1; j < countChunk; ++j)
		{
			vector<string> block2;
			read_data(size_buffer, block2, data);
			vector<string> mergeBlock;		
			merge(block1, block2, mergeBlock);
			for (int k = 0; k < block1.size(); ++k)
			{
				block1[k] = mergeBlock[k];
			}			
			for (int k = 0; k < block2.size(); ++k)
			{
				newData << mergeBlock[block1.size() + k] << '\n';
			}						
		}	
		for (int j = 0; j < block1.size(); ++j)
		{
			ans << block1[j] << '\n';
		}		
		swap(name1, name2);
		data.close();
		newData.close();
	}

    return 0;
}

