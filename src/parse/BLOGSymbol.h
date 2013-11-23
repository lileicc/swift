template <class Object>
class BLOGSymbol{
  int line;
  int column;
  Object val;
  public:
    void symbol (int l, int c){
      line = l;
      column = c;
    }
    void symbol (int l, int c, Object v){
      line = l;
      column = c;
      val = v;
    }
    int getLine(void){
      return line;
    }
    int getColumn(void){
      return column;
    }
    Object getValue(void){
      return val;
    }
};