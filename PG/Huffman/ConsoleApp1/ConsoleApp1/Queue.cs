using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Queue<T> where T : IComparable
    {
        protected List<T> lst = new List<T>();

        public virtual int Count
        {
            get { return lst.Count; }
        }

        public virtual void Add(T val)
        {
            lst.Add(val);
            SetAt(lst.Count - 1, val);
            UpHeap(lst.Count - 1);
        }

        public virtual T Peek()
        {
            if (lst.Count == 0)
            {
                throw new IndexOutOfRangeException("Peeking at an empty priority queue");
            }

            return lst[0];
        }

        public virtual T Pop()
        {
            if (lst.Count == 0)
            {
                throw new IndexOutOfRangeException("Popping an empty priority queue");
            }

            T valRet = lst[0];

            SetAt(0, lst[lst.Count - 1]);
            lst.RemoveAt(lst.Count - 1);
            DownHeap(0);
            return valRet;
        }

        protected virtual void SetAt(int i, T val)
        {
            lst[i] = val;
        }

        protected bool RightSonExists(int i)
        {
            return RightChildIndex(i) < lst.Count;
        }

        protected bool LeftSonExists(int i)
        {
            return LeftChildIndex(i) < lst.Count;
        }

        protected int ParentIndex(int i)
        {
            return (i - 1) / 2;
        }

        protected int LeftChildIndex(int i)
        {
            return 2 * i + 1;
        }

        protected int RightChildIndex(int i)
        {
            return 2 * (i + 1);
        }

        protected T ArrayVal(int i)
        {
            return lst[i];
        }

        protected T Parent(int i)
        {
            return lst[ParentIndex(i)];
        }

        protected T Left(int i)
        {
            return lst[LeftChildIndex(i)];
        }

        protected T Right(int i)
        {
            return lst[RightChildIndex(i)];
        }

        protected void Swap(int i, int j)
        {
            T valHold = ArrayVal(i);
            SetAt(i, lst[j]);
            SetAt(j, valHold);
        }

        protected void UpHeap(int i)
        {
            while (i > 0 && ArrayVal(i).CompareTo(Parent(i)) > 0)
            {
                Swap(i, ParentIndex(i));
                i = ParentIndex(i);
            }
        }

        protected void DownHeap(int i)
        {
            while (i >= 0)
            {
                int iContinue = -1;

                if (RightSonExists(i) && Right(i).CompareTo(ArrayVal(i)) > 0)
                {
                    iContinue = Left(i).CompareTo(Right(i)) < 0 ? RightChildIndex(i) : LeftChildIndex(i);
                }
                else if (LeftSonExists(i) && Left(i).CompareTo(ArrayVal(i)) > 0)
                {
                    iContinue = LeftChildIndex(i);
                }

                if (iContinue >= 0 && iContinue < lst.Count)
                {
                    Swap(i, iContinue);
                }

                i = iContinue;
            }
        }
    }

    internal class HuffmanNode<T> : IComparable
    {
        internal HuffmanNode(double probability, T value)
        {
            Probability = probability;
            LeftSon = RightSon = Parent = null;
            Value = value;
            IsLeaf = true;
        }

        internal HuffmanNode(HuffmanNode<T> leftSon, HuffmanNode<T> rightSon)
        {
            LeftSon = leftSon;
            RightSon = rightSon;
            Probability = leftSon.Probability + rightSon.Probability;
            leftSon.IsZero = true;
            rightSon.IsZero = false;
            leftSon.Parent = rightSon.Parent = this;
            IsLeaf = false;
        }

        internal HuffmanNode<T> LeftSon { get; set; }
        internal HuffmanNode<T> RightSon { get; set; }
        internal HuffmanNode<T> Parent { get; set; }
        internal T Value { get; set; }
        internal bool IsLeaf { get; set; }

        internal bool IsZero { get; set; }

        internal int Bit
        {
            get { return IsZero ? 0 : 1; }
        }

        internal bool IsRoot
        {
            get { return Parent == null; }
        }

        internal double Probability { get; set; }

        public int CompareTo(object obj)
        {
            return -Probability.CompareTo(((HuffmanNode<T>)obj).Probability);
        }
    }
}