#include <SDL.h>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

const int ArraySize = 130;

class Algorithms
{
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    int RectangleSize;

    int Array[ArraySize];
    int B_Array[ArraySize];

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool complete;

public:
    Algorithms() :SCREEN_WIDTH(850), SCREEN_HEIGHT(600), RectangleSize(7), window(NULL), renderer(NULL), complete(false)
    {
        for (int i = 0; i < ArraySize; i++)
        {
            Array[i] = B_Array[i] = NULL;
        }
    }

    void init()
    {
        window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    void close()
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;

        SDL_DestroyWindow(window);
        window = NULL;

        SDL_Quit();
    }

    void visualize(int x = -1, int y = -1, int z = -1)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        int j = 0;

        for (int i = 0; i <= SCREEN_WIDTH - RectangleSize; i += RectangleSize)
        {
            SDL_Rect rect = { i, 0, RectangleSize, Array[j] };
            if (complete)
            {
                SDL_SetRenderDrawColor(renderer, 210, 4, 45, 0);
                SDL_RenderDrawRect(renderer, &rect);
            }
            else if (j == x || j == z)
            {
                SDL_SetRenderDrawColor(renderer, 196, 180, 84, 0);
                SDL_RenderFillRect(renderer, &rect);
            }
            else if (j == y)
            {
                SDL_SetRenderDrawColor(renderer, 176, 224, 230, 0);
                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 196, 160, 84, 0);
                SDL_RenderDrawRect(renderer, &rect);
            }
            j++;
        }
        SDL_RenderPresent(renderer);
    }

    void bubbleSort()
    {
        for (int i = 0; i < ArraySize - 1; i++)
        {
            for (int j = 0; j < ArraySize - 1 - i; j++)
            {
                if (Array[j + 1] < Array[j])
                {
                    swap(Array[j], Array[j + 1]);

                    visualize(j + 1, j, ArraySize - i);
                }
                SDL_Delay(2);
            }
        }
    }

    void insertionSort()
    {
        for (int i = 1; i < ArraySize; i++)
        {
            int j = i - 1;
            int temp = Array[i];
            while (j >= 0 && Array[j] > temp)
            {
                Array[j + 1] = Array[j];
                j--;

                visualize(i, j + 1);
                SDL_Delay(5);
            }
            Array[j + 1] = temp;
        }
    }

    void selectionSort()
    {
        int minIndex;
        for (int i = 0; i < ArraySize - 1; i++)
        {
            minIndex = i;
            for (int j = i + 1; j < ArraySize; j++)
            {
                if (Array[j] < Array[minIndex])
                {
                    minIndex = j;
                    visualize(i, minIndex);
                }
                SDL_Delay(1);
            }
            swap(Array[i], Array[minIndex]);
        }
    }


    void inplaceHeapSort(int* Array, int ArraySize)
    {
        for (int i = 1; i < ArraySize; i++)
        {
            int Temp;
            int childIndex = i;
            int parentIndex = (childIndex - 1) / 2;

            while (childIndex > 0)
            {
                if (Array[childIndex] > Array[parentIndex])
                {
                    Temp = Array[parentIndex];
                    Array[parentIndex] = Array[childIndex];
                    Array[childIndex] = Temp;
                }
                else
                {
                    break;
                }

                visualize(parentIndex, childIndex);
                SDL_Delay(40);

                childIndex = parentIndex;
                parentIndex = (childIndex - 1) / 2;
            }
        }

        for (int heapLast = ArraySize - 1; heapLast >= 0; heapLast--)
        {
            int temp = Array[0];
            Array[0] = Array[heapLast];
            Array[heapLast] = temp;

            int parentIndex = 0;
            int leftChildIndex = 2 * parentIndex + 1;
            int rightChildIndex = 2 * parentIndex + 2;

            while (leftChildIndex < heapLast)
            {
                int maxIndex = parentIndex;

                if (Array[leftChildIndex] > Array[maxIndex])
                {
                    maxIndex = leftChildIndex;
                }
                if (rightChildIndex < heapLast && Array[rightChildIndex] > Array[maxIndex])
                {
                    maxIndex = rightChildIndex;
                }
                if (maxIndex == parentIndex)
                {
                    break;
                }

                int temp = Array[parentIndex];
                Array[parentIndex] = Array[maxIndex];
                Array[maxIndex] = temp;

                visualize(maxIndex, parentIndex, heapLast);
                SDL_Delay(40);

                parentIndex = maxIndex;
                leftChildIndex = 2 * parentIndex + 1;
                rightChildIndex = 2 * parentIndex + 2;
            }
        }
    }

    void gnomeSort(int Array[], int ArraySize)
    {
        int index = 0;

        while (index < ArraySize)
        {
            if (index == 0 || Array[index] == Array[index - 1])
            {
                index++;
            }
            else
            {
                swap(Array[index], Array[index - 1]);
                index--;
                visualize(index - 1, index);
                SDL_Delay(5);
            }
        }
        return;
    }

    void oddEvenSort(int Array[], int Size)
    {
        bool isSorted = false;

        while (!isSorted)
        {
            isSorted = true;

            for (int i = 1; i <= Size - 2; i = i + 2)
            {
                if (Array[i] > Array[i + 1])
                {
                    swap(Array[i], Array[i + 1]);
                    isSorted = false;
                }
            }

            for (int i = 0; i <= Size - 2; i = i + 2)
            {
                if (Array[i] > Array[i + 1])
                {
                    swap(Array[i], Array[i + 1]);
                    isSorted = false;
                    visualize(Array[i - 1], Array[i]);
                    SDL_Delay(5);
                }
            }
        }

        return;
    }

    void loadArr()
    {
        memcpy(Array, B_Array, sizeof(int) * ArraySize);
    }

    void randomizeAndSaveArray()
    {
        unsigned int seed = (unsigned)time(NULL);
        srand(seed);
        for (int i = 0; i < ArraySize; i++)
        {
            int random = rand() % (SCREEN_HEIGHT);
            B_Array[i] = random;
        }
    }

    void execute()
    {
        init();

        randomizeAndSaveArray();
        loadArr();
        const auto start = chrono::high_resolution_clock::now();

        SDL_Event e;
        bool quit = false;

        while (!quit)
        {
            cout << "\nEnter command: ";
            string userInput;
            getline(cin, userInput);

            const auto algorithmStart = chrono::high_resolution_clock::now(); // Track the start time for each algorithm

            switch (userInput[0])
            {
            case '-1':
                quit = true;
                complete = false;
                cout << "\nEXITING SORTING VISUALIZER.\n";
                break;
            case '0':
                randomizeAndSaveArray();
                complete = false;
                loadArr();
                cout << "\nNEW RANDOM LIST GENERATED.\n";
                break;
            case '1':
                loadArr();
                cout << "\nSELECTION SORT STARTED.\n";
                complete = false;
                selectionSort();
                complete = true;
                cout << "\nSELECTION SORT COMPLETE.\n";
                break;
            case '2':
                loadArr();
                cout << "\nINSERTION SORT STARTED.\n";
                complete = false;
                insertionSort();
                complete = true;
                cout << "\nINSERTION SORT COMPLETE.\n";
                break;
            case '3':
                loadArr();
                cout << "\nBUBBLE SORT STARTED.\n";
                complete = false;
                bubbleSort();
                complete = true;
                cout << "\nBUBBLE SORT COMPLETE.\n";
                break;
            case '4':
                loadArr();
                cout << "\nHEAP SORT STARTED.\n";
                complete = false;
                inplaceHeapSort(Array, ArraySize);
                complete = true;
                cout << "\nHEAP SORT COMPLETE.\n";
                break;
            case '5':
                loadArr();
                cout << "\nGNMOE SORT STARTED.\n";
                complete = false;
                gnomeSort(Array, 130);
                complete = true;
                cout << "\nGNOME SORT COMPLETE.\n";
                break;
            case '6':
                loadArr();
                cout << "\nODD/EVEN SORT STARTED.\n";
                complete = false;
                oddEvenSort(Array, 130);
                complete = true;
                cout << "\nODD/EVEN SORT COMPLETE.\n";
                break;
            default:
                cout << "\nInvalid command.\n";
            }

            const auto algorithmEnd = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = algorithmEnd - algorithmStart;
            cout << "Algorithm Elapsed Time:\t" << elapsed.count() << " s\n";

            visualize();
        }

        close();
    }


    bool controls()
    {
        cout << "Available Controls inside Sorting Visualizer:-\n"
            << "Use 0 to Generate a different randomized list.\n"
            << "Use 1 to start Selection Sort Algorithm.\n"
            << "Use 2 to start Insertion Sort Algorithm.\n"
            << "Use 3 to start Bubble Sort Algorithm.\n"
            << "Use 4 to start Heap Sort Algorithm.\n"
            << "Use 5 to start Gnome Sort Algorithm.\n"
            << "Use 6 to start Odd/Even Sort Algorithm.\n"
            << "PRESS ENTER TO START SORTING VISUALIZER...\n"
            << "Or type -1 and press ENTER to quit the program.";

        string s;
        getline(cin, s);
        if (s == "-1")
        {
            return false;
        }
        return true;
    }

    void intro()
    {
        cout << "==============================Sorting Visualizer==============================\n\n"
            << "Visualization of different sorting algorithms in C++ with SDL2 Library. A sorting algorithm is an algorithm that puts the elements of a list in a certain order. While there are a large number of sorting algorithms, in practical implementations a few algorithms predominate.\n"
            << "In this implementation of sorting visualizer, we'll be looking at some of these sorting algorithms and visually comprehend their working.\n"
            << "The sorting algorithms covered here are Selection Sort, Insertion Sort, Bubble Sort, Merge Sort, Quick Sort and Heap Sort.\n"
            << "The list size is fixed to 130 elements. You can randomize the list and select any type of sorting algorithm to call on the list from the given options. Here, all sorting algorithms will sort the elements in ascending order. The sorting time being visualized for an algorithm is not exactly same as their actual time complexities. The relatively faster algorithms like Merge Sort, etc. have been delayed so that they could be properly visualized.\n\n"
            << "Press ENTER to show controls...";

        string s;
        getline(cin, s);
        if (s == "\n")
        {
            return;
        }
    }
};



int main(int argc, char* args[])
{
    Algorithms Algo;
    Algo.intro();

    while (1)
    {
        cout << '\n';

        if (Algo.controls())
        {
            Algo.execute();
        }
        else
        {
            cout << "\nEXITING PROGRAM.\n";
            break;
        }
    }
    return 0;
}