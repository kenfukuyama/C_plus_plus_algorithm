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

void passbyValue(ResizableArray arr) {
    arr.append(2);
}

void passbyReference(ResizableArray& arr) {
    arr.append(3);
}

void passbyPointer(ResizableArray* arr) {
    arr->append(4);
}


//----------------------------------------------------------------------------------------------------------------------

long minPos(const ResizableArray& arr, long start, long end) {
    long value = arr.data[start];
    long pos = start;
 
    cout << "Running " << endl;
 
    for (long i = start; i < end; i++) {
        if (arr.data[i] < value) {
            value = arr.data[i];
            pos = i;
        }
    }
    return pos;
}

void selectionSort(ResizableArray& arr) {
    for (long i = 0; i < arr.counter; i++) {
        long j = minPos(arr, i, arr.counter);
        long temp = arr.data[i];
        arr.data[i] = arr.data[j];
        arr.data[j] = temp;
    }

}


int main()
{
    ResizableArray nums;

    nums.append(0);
    // nums.append(4);
    // nums.append(6);
    // nums.append(2);
    // nums.append(3);
    // nums.append(19);
    // nums.append(7);

    cout << nums << endl;

    selectionSort(nums);


    // // Pass by value;
    // passbyValue(nums);

    // // Pass by reference;
    // passbyReference(nums);

    // // Pass by pointer;
    // passbyPointer(&nums);

    cout << nums;


//      string a = "";
    
//     cout << "What's your name? ";
//     cin >> a;
//     cout << a << endl;
}

