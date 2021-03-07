#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using std::vector;

void print_grid(const vector<vector<int>>& grid)
{
	for (int y = 0; y < 9; y++) 
	{
		if (y % 3 == 0 && y != 0)
			std::cout << "---------------------\n";

		for (int x = 0; x < 9; x++)
		{
			if (x % 3 == 0 && x != 0)
				std::cout << "| ";

			if (grid[y][x] == 0)
				std::cout << ". ";
			else
				std::cout << grid[y][x] << ' ';
		}
		std::cout << '\n';
	}
}

vector<vector<int>> load_grid(std::string filename)
{
	vector<vector<int>> grid;

	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			vector<int> row;
			for (char ch : line)
			{
				if (isdigit(ch))
					row.push_back(ch - '0'); // Convert char to int
				else
					row.push_back(0);
			}
			grid.push_back(row);
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file \"" << filename << "\" \n";
		// Return 2D vector with all values 0
		vector<vector<int>> blank(9, vector<int>(9, 0));
		return blank;
	}
	return grid;
}

bool possible(const vector<vector<int>>& grid, int x, int y, int num)
{
	// Check row
	for (int i = 0; i < 9; i++)
	{
		if (grid[y][i] == num)
			return false;
	}
	// Check column
	for (int i = 0; i < 9; i++)
	{
		if (grid[i][x] == num)
			return false;
	}
	// Check 3x3 square
	int square_x = x / 3 * 3;
	int square_y = y / 3 * 3;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) 
		{
			if (grid[square_y + i][square_x + j] == num)
				return false;
		}
	}
	return true;
}

bool solve(vector<vector<int>>& grid)
{
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++)
		{
			// Find empty square
			if (grid[y][x] == 0)
			{
				// Try all possible choices
				for (int num = 1; num <= 9; num++)
				{
					if (possible(grid, x, y, num))
					{
						grid[y][x] = num;
						if (solve(grid)) // Recursion! :O
							return true;
						grid[y][x] = 0;  // Erase bad choice - backtrack
					}
				}
				return false;
			}
		}
	}
	return true;
}

int main()
{
	auto grid = load_grid("grid.txt");

	print_grid(grid);
	std::cout << '\n';
	solve(grid);
	print_grid(grid);
}
