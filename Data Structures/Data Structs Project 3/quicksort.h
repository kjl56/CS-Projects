//kyle Lugo
//kjl56@zips.uakron.edu
//Data Structures Project III
template <typename Comparable>
const Comparable & median3( std::vector<Comparable> & a, int left, int right )
{
  int center = ( left + right ) / 2;
  if( a[ center ] < a[ left ] )
    std::swap( a[ left ], a[ center ] );
  if( a[ right ] < a[ left ] )
    std::swap( a[ left ], a[ right ] );
  if( a[ right ] < a[ center ] )
    std::swap( a[ center ], a[ right ] );
  // Place pivot at position right - 1
  std::swap( a[ center ], a[ right - 1 ] );
  return a[ right - 1 ];
}

template <typename Comparable>
void quicksort( std::vector<Comparable> & a, int left, int right )
{
  if (right - left <= 1)
  {
    if (a[left] > a[right])
    {
      std::swap(a[right],a[left]);
    }
  }
  else
  {
    const Comparable & pivot = median3( a, left, right );
    // Begin partitioning
    int i = left, j = right - 1;
    for( ; ; )
    {
      while( a[ ++i ] < pivot ) { }
      while( pivot < a[ --j ] ) { }
      if( i < j )
        std::swap( a[ i ], a[ j ] );
      else
        break;
    }
    std::swap( a[ i ], a[ right - 1 ] );
    quicksort( a, left, i - 1 );
    quicksort( a, i + 1, right );
  }
}

template <typename Comparable>
void quicksort( std::vector<Comparable> & a )
{
  quicksort( a, 0, a.size( ) - 1 );
}
