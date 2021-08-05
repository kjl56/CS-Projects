#ifndef MAZECELL_H_INCLUDED
#define MAZECELL_H_INCLUDED

class mazeCell{

public:

   // no param constructor
   explicit mazeCell ()
      : left(true), right(true),
      top(true), bot(true) {};

   // 4 parameter constructor for special cells (cell 0 and the last cell)
   mazeCell(bool l, bool r, bool t, bool b)
      : left(l), right(r),
      top(t), bot(b) {};

   // accessors
   int getLeft() const {return left;}
   int getRight() const {return right;}
   int getTop() const {return top;}
   int getBot() const {return bot;}

   // mutators
   void setLeft(bool l) {left = l;}
   void setRight(bool r) {right = r;}
   void setTop(bool t) {top = t;}
   void setBot(bool b) {bot = b;}

private:
     bool left, right, top, bot;
};

#endif // MAZECELL_H_INCLUDED
