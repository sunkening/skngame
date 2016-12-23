#pragma once
namespace skn
{


class SequenceAlgorithm {
public:
	template<class v>
	static void SelectionSort(vector<v> *array) {
		vector<v>::iterator iter_i;
		vector<v>::iterator iter_j;
		for (iter_i = array->begin(); iter_i != array->end()-1; iter_i++) {
			vector<v>::iterator minIter = iter_i;
			for (iter_j = iter_i + 1; iter_j != array->end();iter_j++) {
				if (*iter_j<*minIter) {
					minIter = iter_j;
				}
			}
			v temp = *iter_i;
			*iter_i = *minIter;
			*minIter = temp;
		}
	}
};

}