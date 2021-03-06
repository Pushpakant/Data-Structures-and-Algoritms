template <typename T>
class SegmentTree {
   public:
    T leftmost, rightmost;  //  extreme points of tree

    SegmentTree<T>* leftChild;   //  left tree
    SegmentTree<T>* rightChild;  //  right tree

    //  range sum queries
    T sum;

    SegmentTree(T startIdx, T endIdx, T* arr) : leftmost(startIdx), rightmost(endIdx) {
        if (this->leftmost == this->rightmost) {
            //  leaf
            this->sum = arr[this->leftmost];  //  filling the segment tree from left

            this->leftChild = nullptr;
            this->rightChild = nullptr;
        } else {
            //  have two children
            T mid = this->leftmost + (this->rightmost - this->leftmost) / 2;

            //  using postorder to calculate sum again
            this->leftChild = new SegmentTree<T>(this->leftmost, mid, arr);
            this->rightChild = new SegmentTree<T>(mid + 1, this->rightmost, arr);

            this->sum = this->leftChild->sum + this->rightChild->sum;
        }
    }

    //  no lazy propagation implemented
    void update(T index, T val) {
        if (this->leftmost == this->rightmost) {
            //  leaf
            this->sum = val;
            return;
        }

        // have two children
        if (index <= this->leftChild->rightmost) {
            this->leftChild->update(index, val);
        } else {
            this->rightChild->update(index, val);
        }

        // recalculating sum after update
        this->sum = this->leftChild->sum + this->rightChild->sum;
    }

    void update(T startIdx, T endIdx, T val) {
        if (this->leftmost == this->rightmost) {
            //  leaf
            this->sum = val;
            return;
        }

        //  value of rightMost will be the upperbound in this subtree
        if (startIdx <= this->leftChild->rightmost) {
            this->leftChild->update(startIdx, endIdx, val);
        }

        //  value of leftMost will be the lowerbound in this subtree
        if (startIdx >= this->rightChild->leftmost) {
            this->rightChild->update(startIdx, endIdx, val);
        }

        //  value of rightMost will be the upperbound in this subtree
        if (endIdx <= this->leftChild->rightmost) {
            this->leftChild->update(startIdx, endIdx, val);
        }

        //  value of leftMost will be the lowerbound in this subtree
        if (endIdx >= this->rightChild->leftmost) {
            this->rightChild->update(startIdx, endIdx, val);
        }

        // recalculating sum after update
        this->sum = this->leftChild->sum + this->rightChild->sum;
    }

    T rangeSum(T l, T r) {
        //  entirely disjoint
        if (l > rightmost || r < leftmost) return 0;

        //  complete overlap
        if (l <= leftmost && r >= rightmost) return sum;

        //  partial overlap
        return this->leftChild->rangeSum(l, r) + this->rightChild->rangeSum(l, r);
    }

    ~SegmentTree() {
        if (this->leftChild != nullptr) delete this->leftChild;
        if (this->rightChild != nullptr) delete this->rightChild;
    }
};
