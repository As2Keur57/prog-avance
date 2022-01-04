#include "Node.hpp"

Node::Node()
{
	this->pos = Point();
	this->cost = 0;
	this->heuristic = 0;
}

Node::Node(Node* n)
{
	this->pos = Point(n->getX(), n->getY());
	this->cost = n->getCost();
	this->heuristic = n->getHeuristic();
}

Node::Node(Point* p, int c, int h)
{
	this->pos = Point(p);
	this->cost = c;
	this->heuristic = h;

}

Node::~Node()
{

}

Point Node::getPosition()
{
	return pos;
}

int Node::getCost()
{
	return cost;
}

int Node::getHeuristic()
{
	return heuristic;
}

int Node::getX()
{
	return getPosition().getX();
}

int Node::getY()
{
	return getPosition().getY();
}

void Node::setPosition(Point* p)
{
	this->pos = p;
}

void Node::setCost(int newCost)
{
	this->cost = newCost;
}

void Node::setHeuristic(int newHeuristic)
{
	this->heuristic = newHeuristic;
}

list<Point> AStar::way(int** mat, int nbCol, int nbRow, Point start, Point goal)
{
	Node startWay = Node(&start, 0, 0);

	bool visited[nbRow][nbCol];
    memset(visited, false, sizeof visited);

    int rowNum[] = {-1, 0, 0, 1};
	int colNum[] = {0, -1, 1, 0};

	list<Node> open;
	list<Node> close;

	open.push_front(startWay);
	visited[startWay.getX()][startWay.getY()] = true;

	while (!open.empty())
    {
        Node curr = open.back();
        Point pt = curr.getPosition();
        
        if (pt.getX() == goal.getX() && pt.getY() == goal.getY())
        {
        	close.push_front(curr);
            return way(close);
        }
        
        open.pop_back();
 		close.push_front(curr);
 		
        for (int i = 0; i < 4; i++)
        {
            int row = pt.getX() + rowNum[i];
            int col = pt.getY() + colNum[i];
             
            if (((row >= 0 && row < nbRow) && (col >= 0 && col <= nbCol))  && mat[row][col] == 0 && 
               !visited[row][col])
            {
                visited[row][col] = true;
                Node adj = Node(new Point(row,col), 1, 1+curr.getHeuristic());
                open.push_front(adj);
            }
        }
    }
    exit(0);
}



Node AStar::bestAdj(Node n1, list<Node> l)
{
	list<Node> adj = {};
	Node tmp;

	for(list<Node>::reverse_iterator it = l.rbegin(); it != l.rend(); it++)
	{
		if(it->getPosition().getX() == n1.getX()+1 && it->getPosition().getY() == n1.getY())
			adj.push_front(*it);
		if(it->getPosition().getX() == n1.getX()-1 && it->getPosition().getY() == n1.getY())
			adj.push_front(*it);
		if(it->getPosition().getX() == n1.getX() && it->getPosition().getY() == n1.getY()+1)
			adj.push_front(*it);
		if(it->getPosition().getX() == n1.getX() && it->getPosition().getY() == n1.getY()-1)
			adj.push_front(*it);
	}

	tmp = adj.front();
	adj.pop_front();

	while(!adj.empty())
	{
		if(tmp.getHeuristic() > adj.front().getHeuristic())
			tmp = adj.front();
		adj.pop_front();
	}

	return tmp;
}

list<Point> AStar::way(list<Node> l)
{
	list<Point> way;

	Node tmp = l.front();
	l.pop_front();

	way.push_front(tmp.getPosition());

	if(l.size() > 0)
	{
		while(tmp.getX() != l.back().getX() || tmp.getY() != l.back().getY())
		{
			tmp = bestAdj(tmp, l);
			way.push_front(tmp.getPosition());
		}
	}

	return way;
}

