#include <iostream>
#include <vector>
#include <string>
#include <ostream>

using namespace std;


struct ResizableArray {
    // This is the poiner to the start of our array
    long* data;
    
    // Keep track of how much memory we have allocated
    long size;
    
    // Keep track of how much memory we have used
    long counter;
    
    // A default constructor
    ResizableArray(){
        // Start off by allocating memory for 1 int
        data = new long[1];
        
        // This means we have allocated for 1
        size = 1;
        
        // And we are currently using 0
        counter = 0;
    }

	// This is a copy constructor. It specifies what happens when
	// the array needs to be copied. In this case it performs
	// a deep copy, which is what we need
	ResizableArray(const ResizableArray& other){
		size = other.size;
		counter = other.counter;
		data = new long[other.size];

		for (long i = 0; i < other.size; i++){
			data[i] = other.data[i];
		}
	}

	// Overloading the == operator. Now we can compare 
	// two ResizableArrays with the == operator
	bool operator==(const ResizableArray rhs) const {
		// If the sizes or counters are different, it's not a match
		if (size != rhs.size){
			return false;
		}
		if (counter != rhs.counter){
			return false;
		}

		// Assume the arrays match
		bool same = true;

		// And try to find a contradiction
		for (long i = 0; i < counter; i++){
			if (data[i] != rhs.data[i]){
				return false;
			}
		}
		
		// Colud not get a contradiction
		return true;
	}
    
    // Print the contents we have
    void print(){
        for (long i = 0; i < counter; i++){
            std::cout << data[i] << std::endl;
        }
    }
    
	// Get the value at a specified position
    int get(long index){
        return data[index];
    }
    
	// Set the value at a specified position with a given integer
    void set(long index, long value){
        data[index] = value;
    }

	void insert(long index, long value){
        if (index < size){
            for(long i = counter; i > index; i--){
                data[i] = data[i-1];
            }
            data[index] = value;
            counter++;
            if (counter == size){
                long oldSize = size;
                
                size = size * 2;
                
                long* newArr = new long[size];
            
                for (long i = 0; i < oldSize; i++) {
                    newArr[i] = data[i];
                }
                
                delete[] data;
                
                data = newArr;
            }
        }
        else{
            int oldSize = size;
            while (index+1 >= size){
                size *=2;
            }
            if (size > oldSize){
                long* newArr = new long[size];
                
                for (long i = 0; i < oldSize; i++) {
                    newArr[i] = data[i];
                }
                
                delete[] data;
                
                data = newArr;
            }
            
            for (long i = counter; i < index; i++){
                data[i] = 0;
            }
            
            data[index] = value;
            counter = index + 1;
        }
    }
    
    
    // Store a new value in the array
    void append(long value){
        // The very first time this is called
        // we know we have enough storage allocated
        // because we allocated space for 1 int
        // so we store it
        data[counter] = value;
        // and increase the counter
        counter++;
        
        // If we are out of space, i.e. we have
        // stored as much as we have allocated
        // then we need to increase our storage space
        if (counter == size){
            // Just for convenience, store the old size
            long oldSize = size;
            
            // Let's double the amount of storage we have
            size = size * 2;
            
            // Allocate another chunk of memory
            // twice as big as the first
            long* newArr = new long[size];
            
            // Copy all elements from the old location
            // to the new location
            for (long i = 0; i < oldSize; i++) {
                newArr[i] = data[i];
            }
            
            // Release the old location
            delete[] data;
            
            // Make our data pointer point to the new location
            data = newArr;
            
        }
    }
	
	// This is called a destructor. It simply releases the 
	// memory we have been using.
	~ResizableArray(){
		delete[] data;
	}
};

// This is an overload of the << operator, which allows us
// to print out the ResizableArray with cout <<
std::ostream& operator<<(std::ostream& os, const ResizableArray& arr) {
    for (long i = 0; i < arr.counter; i++){
		os << arr.data[i] << " ";
	}

    return os;
}

//-- binary search---------------------------------------------------------------------------

bool binearySearch(ResizableArray& arr, long value)  {
    long start = 0;
    long end = arr.counter - 1; // because the end index is one less.
    // putting start because the location of start is not always zero. 
    long mid = start + ((end - start) / 2);

    while (start <= end) {
        if (arr.data[mid] == value) {
            return true;
        }
        else if (arr.data[mid] > value) {
            end = mid - 1;
            mid = start + ((end - start) / 2);
        }
        else if (arr.data[mid] < value) {
            start = mid + 1;
            mid = start + ((end - start) / 2);
        }
    }
    return false;
}


int main() {
    ResizableArray a;
    int size = 10000;
    for (int i = 0; i < size; i++) {
        a.append(i);
    }
    
    // cout << a << endl;  
    long value = 9999;
    cout << "value " << value << " is found: " << boolalpha << binearySearch(a, value);
}
























