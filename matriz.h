#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <limits>

using std::vector;

// matriz cuadrada
template <typename T> class matriz {
public:
   matriz() {}
   explicit matriz(size_t n, const T& x = T()): m(n, vector<T>(n, x)) {}
   size_t dimension() const {return m.size();}
   const vector<T>& operator [](size_t i) const {return m[i];}
   vector<T>& operator [](size_t i) {return m[i];}
private:
   vector< vector<T> > m;
};

template <typename T>
std::ostream& operator << (std::ostream& os, matriz<T> M)
{
	for(int i = 0; i < M.dimension() ; i++)
		{
			for(int j = 0; j < M.dimension() ; j++)
			{
				if(M[i][j] != std::numeric_limits<T>::max())
					os << "[" << M[i][j] << "]\t";
				else
					os << "[" << "-" <<"]\t";
			}
			os << "\n";	
		}
		return os;	
}
#endif  // MATRIZ_H
