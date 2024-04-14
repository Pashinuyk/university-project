// OOP DZ 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <set>

int main()
{
  int N; 
  int M;

  std::cout << "Enter number of rows: ";
  std::cin >> N;
  if (std::cin.fail()) // если предыдущее извлечение было неудачным, эквивалентно if (!cin)
  {
      std::cout << "Invalid type! Changed to 1" << std::endl;
      std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // извлекаем и отбрасываем максимальное количество символов из входного потока до разделителя '\n' включительно
      N = 1;
  }

  std::cout << "Enter number of collumns: ";
  std::cin >> M;
  if (std::cin.fail()) // если предыдущее извлечение было неудачным, эквивалентно if (!cin)
  {
      std::cout << "Invalid type! Changed to 1" << std::endl;
      std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // извлекаем и отбрасываем максимальное количество символов из входного потока до разделителя '\n' включительно
      M = 1;
  }



  //char bukva[1];
  char** matrix = new char* [N];
  for (int i = 0; i < N; i++) {
      matrix[i] = new char[M];
      for (int j = 0; j < M; j++) {
          std::cout << "Enter matrix[" << i << "][" << j << "]: ";
          std::cin >> matrix[i][j];

        //  std::cin >> bukva;
        //  matrix[i][j] = bukva[0];
        //  std::cout << matrix[i][j];
      }
  }

  std::set<char> numbers{};

  for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
          if (j == 0) std::cout << "" << std::endl;
          std::cout << matrix[i][j] << " ";
          numbers.insert(matrix[i][j]);
      }
  }

//ОСВОБОЖДЕНИЕ ПАМЯТИ -------------------

  for (int i = 0; i < N; i++) {
      delete[] matrix[i];
  }
  delete[] matrix;

  std::cout << " " << std::endl;
  std::cout << "Number of non-repeating elements: " << numbers.size() << std::endl;
    
}

