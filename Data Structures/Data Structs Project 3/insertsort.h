template <typename Iterator, typename Comparator>
void insertionSort( const Iterator & begin, const Iterator & end, Comparator lessThan )
{
  if( begin == end )
    return;
  Iterator j;
  for( Iterator p = begin+1; p != end; ++p )
  {
    auto tmp = std::move( *p );
    for( j = p; j != begin && lessThan( tmp, *( j-1 ) ); --j )
      *j = std::move( *(j-1) );
    *j = std::move( tmp );
  }
}

template <typename Iterator>
void insertionSort( const Iterator & begin, const Iterator & end )
{
  insertionSort( begin, end, std::less<decltype(*begin)>{ } );
}
