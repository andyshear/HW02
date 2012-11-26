class Square{
public:
	Square(int depth, ci::Vec2i position, ci::Vec2f initial, float radius);
	
	Square* next_;
	Square* prev_;

	Square* children_;

	ci::Vec2f initial_;
	ci::Vec2i position_; //position_ == mouse position
	float radius_;		
	
	void draw();
	void update( ci::Vec2i &mouseLoc, float parent_r);

	void addChild(int depth);
};

void insertAfter(Square* new_item, Square* insert_here);

