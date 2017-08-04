#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>



#define ARR_SIZE 15
#define int_vector std::vector<int>
#define vector_set  std::set<int_vector>
#define set_set  std::set<int_set>



// this function is needed for std::sort
bool compare (int a, int b) { return a < b; }

// helper function for print_set()
void print_1D_vector( int_vector vec ) {

	std::cout << "[";
	bool first = true;
	for (auto elem : vec) {
		if (!first) { std::cout << ",";} else { first = false; }
		std::cout << elem;
	}
	std::cout << "]";

}

// for print result set in pretty print
void print_set( vector_set my_set ) {

	std::cout << "[ ";
	bool first = true;
	for (auto vec : my_set) {
		if (!first) { std::cout << ", ";} else { first = false; }
		print_1D_vector( vec );
	}
	std::cout << " ]";
	
}


// This function takes in an array of integers and returns a set 
// of triplets that follow the equation a + b + c = 0
vector_set sum_of_three(int * arr, int n ) {
	
	vector_set result;

	// return empty result set
	if ( arr == nullptr || n < 3 )
		return result;
	
	// insert integers into a vector and sort
	int_vector nums;
	for (int i = 0; i < n; i++) {
		nums.push_back( arr[i] );
	}
	std::sort( nums.begin(), nums.end(), compare );
	

	int val_one; 
	for (int i = 0; i < nums.size(); i++) {
		
		// by pulling out certain values we can avoid resorting the vector
		// pull value out of vector and save for later reinsertion 
		val_one = nums[i];
		nums.erase( nums.begin() + i );

		// loop through remainder of array
		int val_two;
		for (int k = 0; k < nums.size(); k++) {
			
			// pull value out of vector and save for later reinsertion
			val_two = nums[k];
			nums.erase( nums.begin() + k );
			
			// theoretical thrid value
			int val_three = -1 * ( val_one + val_two );

			// if the third value is found insert the triplet into the result set
			if ( find( nums.begin(), nums.end(), val_three ) != nums.end() ) {
				int_vector triplet;

				triplet.push_back( val_one );
				triplet.push_back( val_two );
				triplet.push_back( val_three );
				
				// values in triplet sorted before inserted into result set
				std::sort( triplet.begin(), triplet.end(), compare );
				result.insert( triplet );
			}

			//reinsert value that was removed
			nums.insert( nums.begin() + k, val_two);
		}
	
		//reinsert value that was removed
		nums.insert( nums.begin() + i, val_one);

	}

	return result;
}


TEST_CASE("null array and empty array") {
	
	int* empty_array;
	int not_empty[] = {1};

	vector_set empty_set;
	
	// null array
	REQUIRE( sum_of_three( empty_array, 3) == empty_set );
	// length zero parameter
	REQUIRE( sum_of_three( not_empty, 0) == empty_set );
	// Both null array and zero length arguement
	REQUIRE( sum_of_three( empty_array, 0) == empty_set );
}

TEST_CASE("not enough values") {
	int* zero;
	int one[] = {1};
	int two[] = {2};

	vector_set empty_set;

	REQUIRE( sum_of_three( zero, 0 ) == empty_set );
	REQUIRE( sum_of_three( one,  1 ) == empty_set );
	REQUIRE( sum_of_three( two,  2 ) == empty_set );
}

TEST_CASE("one valid triplet") {
	
	int_vector vec_one;
	vec_one.push_back(-2); vec_one.push_back(-1); vec_one.push_back(3);
	vector_set set_one;
	set_one.insert( vec_one );

	int array_one[] = {3, -1, -2};
	int array_two[] = {1, 100, 50, 3, -1, -2};
	int array_three[] = {3, -1, -2, -2, -1, 3};

	REQUIRE( sum_of_three( array_one,   3 ) == set_one);
	REQUIRE( sum_of_three( array_two,   6 ) == set_one);
	REQUIRE( sum_of_three( array_three, 3 ) == set_one); // this will also test duplicates

}


TEST_CASE("no valid triplet") {

	vector_set empty_set;

	int array_one[] = {1,2,3,4,5,6};
	int array_two[] = {-1,-2,-3,-4,-5,-6};
	int array_three[] = {-2,-1,0,100,200};

	
	REQUIRE( sum_of_three( array_one,   6 ) == empty_set );
	REQUIRE( sum_of_three( array_two,   6 ) == empty_set );
	REQUIRE( sum_of_three( array_three, 6 ) == empty_set );

}

TEST_CASE("multiple valid triplets") {


	int_vector vec_one;
	vec_one.push_back(-2); vec_one.push_back(-1); vec_one.push_back(3);	
	int_vector vec_two;
	vec_two.push_back(-10); vec_two.push_back(5); vec_two.push_back(5);
	int_vector vec_three;
	vec_three.push_back(-30); vec_three.push_back(-20); vec_three.push_back(50);


	vector_set set_one;
	set_one.insert( vec_one ); set_one.insert( vec_two );
	vector_set set_two;
	set_two.insert( vec_three ); set_two.insert( vec_one );
	vector_set set_three;
	set_three.insert( vec_two ); set_three.insert( vec_three );

	int arr_1[] = {-2,-1,3,-10, 5, 5};
	int arr_2[] = {-30,-20, 50,-2,-1,3};
	int arr_3[] = {-10,5,5,50,-30,-20};

	REQUIRE( sum_of_three( arr_1 , 6 ) == set_one );
	REQUIRE( sum_of_three( arr_2 , 6 ) == set_two );
	REQUIRE( sum_of_three( arr_3 , 6 ) == set_three );


}
