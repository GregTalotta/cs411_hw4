#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
int substring_count(char first_letter, char second_letter, string input)
{
    int total = 0;
    int total_size = input.size();
    for (int sub_size = 1; sub_size <= total_size; ++sub_size)
    {
        for (int i = 0; i <= total_size - sub_size; ++i)
        {
            if ((input[i] == first_letter) && (input[i + sub_size - 1] == second_letter))
            {
                ++total;
            }
        }
    }
    return total;
}

int substring_efficient(char first_letter, char second_letter, string input)
{
    int total = 0;
    int total_first = 0;
    int total_size = input.size();
    for (int i = 0; i < total_size; ++i)
    {
        if (input[i] == first_letter)
        {
            ++total_first;
        }

        if (input[i] == second_letter)
        {
            total += total_first;
        }
    }
    return total;
}

#include <vector>
using std::vector;
bool matrix_worker(int number, int x, int y, int length, vector<vector<int>> &test_matrix)
{
    if ((x >= test_matrix.size() - 1) || (y >= test_matrix.size() - 1) || (x < 0) || (y < 0))
    {
        return false;
    }
    int mid_size = length / 2;
    int mid_x = x + mid_size;
    int mid_y = y + mid_size;
    int new_length = 0;
    if (length % 2 == 0)
    {
        new_length = length - mid_size + 1;
    }
    else
    {
        new_length = length - mid_size;
    }
    int median = test_matrix[mid_x][mid_y];
    if (length <= 0)
    {
        return (test_matrix[x][y] == number) || (test_matrix[x + 1][y] == number) || (test_matrix[x][y + 1] == number) || (test_matrix[x + 1][y + 1] == number);
    }
    if (median == number)
    {
        return true;
    }
    else if (median > number)
    {
        if (test_matrix[mid_x][y] == number)
        {
            return true;
        }
        else if (test_matrix[mid_x][y] > number)
        {
            if (test_matrix[x][mid_y] > number)
            {
                return matrix_worker(number, x + 0, y + 0, (mid_size - 1), test_matrix);
            }
            else
            { // This will cause Segmentation fault (core dumped) if moved to two bools.
                return (matrix_worker(number, x + 0, y + 0, (mid_size - 1), test_matrix) || matrix_worker(number, x + 0, mid_y, new_length, test_matrix));
            }
        }
        else
        {
            bool q_1 = matrix_worker(number, x + 0, y + 0, (mid_size - 1), test_matrix);
            bool q_2 = matrix_worker(number, x + 0, mid_y, new_length, test_matrix);
            bool q_3 = matrix_worker(number, mid_x, y + 0, new_length, test_matrix);
            return (q_1 || q_2 || q_3);
        }
    }
    else
    {
        bool q_1 = matrix_worker(number, x + 0, y + 0, (mid_size - 1), test_matrix);
        bool q_2 = matrix_worker(number, x + 0, mid_y, new_length, test_matrix);
        bool q_3 = matrix_worker(number, mid_x, y + 0, new_length, test_matrix);
        bool q_4 = matrix_worker(number, mid_x, mid_y, new_length, test_matrix);
        return (q_1 || q_2 || q_3 || q_4);
    }

    return false;
}
bool matrix_search(int number, vector<vector<int>> &test_matrix)
{
    if ((number > test_matrix[test_matrix.size() - 1][test_matrix.size() - 1]) || ((number > test_matrix[test_matrix.size() - 1][test_matrix.size() - 1]) && (number > test_matrix[test_matrix.size() - 1][test_matrix.size() - 1])))
    {
        return false;
    }
    return matrix_worker(number, 0, 0, test_matrix.size() - 1, test_matrix);
}

int main()
{
    string test = "CABAAXBYA";
    cout << "A. L 3.2/8 - A:    " << substring_count('A', 'B', test) << endl;
    cout << "A. L 3.2/8 - B:    " << substring_efficient('A', 'B', test) << endl;
    cout << "\n";
    vector<vector<int>> test_m = {{10, 11, 12}, {20, 21, 22}, {30, 31, 32}};
    for (int i = 0; i < test_m.size(); ++i)
    {
        for (int j = 0; j < test_m.size(); ++j)
        {
            cout << test_m[j][i] << " ";
        }
        cout << endl;
    }
    int num = 0;
    cout << "enter the number to search for" << endl;
    std::cin >> num;
    bool te = matrix_search(num, test_m);
    cout << "A. L 4.5/13:    " << te << endl;
    return 0;
}