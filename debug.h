#ifndef DEBUG_H_
#define DEBUG_H_

#ifndef LOUD_TRACKEDOBJECT
#define LOUD_TRACKEDOBJECT 0
#endif
#include <iostream>

namespace debug {

struct Loud
{
	static int constructed;
	static int copied;
	static int moved;
	static int assigned;
	static int move_assigned;
	int i;
	Loud() : i(constructed++) {std::cerr << "default constructed " << i << std::endl;}
	Loud(const char* str) : i(constructed++) {std::cerr << "constructed " << i << " with parameter: " << str << std::endl;}
	Loud(Loud&& a) noexcept : i(constructed++) {++moved; std::cerr << "move constructed " << i << " from " << a.i << std::endl;}
	Loud(const Loud& a) : i(constructed++) {++copied; std::cerr << "copy constructed " << i << " from " << a.i << std::endl;}
	Loud& operator=(const Loud& a) {++assigned; std::cerr << "assigned " << a.i << " to " << i << std::endl; return *this;}
	Loud& operator=(Loud&& a) noexcept {++move_assigned; std::cerr << "move assigned " << a.i << " to " << i << std::endl; return *this;}
	~Loud() {std::cerr << "destructed " << i << std::endl;}
	void hello(){std::cerr << "hello from " << i << std::endl;}
	bool operator<(const Loud& a) const {return i < a.i;}
	bool operator==(const Loud& a) const {return i == a.i;}
	friend std::ostream& operator<<(std::ostream& os, const Loud& a);
};

struct TrackedObject {
	struct Result {
		std::size_t def;
		std::size_t copied;
		std::size_t moved;
		std::size_t assigned;
		std::size_t move_assigned;
		std::size_t destroyed;
		std::size_t from_val;
		Result() = default;
		Result(std::size_t a, std::size_t b, std::size_t c, std::size_t d, std::size_t e, std::size_t f, std::size_t g) : 
			def(a),
			copied(b),
			moved(c),
			assigned(d),
			move_assigned(e),
			destroyed(f),
			from_val(g) {}
		Result operator-(const Result& r) {
			return Result(
				def - r.def, 
				copied - r.copied,
				moved - r.moved,
				assigned - r.assigned,
				move_assigned - r.move_assigned,
				destroyed - r.destroyed,
				from_val - r.from_val
			);
		}
		bool operator == (const Result& r) {
			return def == r.def &&
				copied == r.copied &&
				moved == r.moved &&
				assigned == r.assigned &&
				move_assigned == r.move_assigned &&
				destroyed == r.destroyed &&
				from_val == r.from_val;
		}
	};
	static Result current;
	static Result last;
	static void beginTracking() { last = current; }
	static Result getResult() { return current - last; }
	std::size_t i;
	TrackedObject() : i(0) {current.def++; 
#if LOUD_TRACKEDOBJECT		
		std::cout << "default constructed\n";
#endif
	}
	TrackedObject(std::size_t n) : i(n) {current.from_val++; 
#if LOUD_TRACKEDOBJECT		
		std::cout << "value constructed\n";
#endif
	}
	TrackedObject(TrackedObject&& a) noexcept : i(a.i) {++current.moved; 
#if LOUD_TRACKEDOBJECT		
		std::cout << "move constructed\n";
#endif
	}
	TrackedObject(const TrackedObject& a) : i(a.i) {++current.copied; 
#if LOUD_TRACKEDOBJECT		
		std::cout << "copy constructed\n";
#endif
	}
	TrackedObject& operator=(const TrackedObject& a) {i = a.i; ++current.assigned; 
#if LOUD_TRACKEDOBJECT		
		std::cout << "assignment\n"; 
#endif
	return *this;
	}
	TrackedObject& operator=(TrackedObject&& a) noexcept {i = a.i; ++current.move_assigned; 
#if LOUD_TRACKEDOBJECT		
		std::cout << "move assignment\n";
#endif
	return *this;
	}
	~TrackedObject() {++current.destroyed;
#if LOUD_TRACKEDOBJECT		
		std::cout << "destroyed\n";
#endif
	}
	bool operator<(const TrackedObject& a) const {return i < a.i;}
	bool operator==(const TrackedObject& a) const {return i == a.i;}
};

typedef Loud LoudObject;

std::ostream& operator<<(std::ostream& os, const Loud& a) {
	os << a.i;
	return os;
}

int Loud::constructed = 0;
int Loud::copied = 0;
int Loud::moved = 0;
int Loud::assigned = 0;
int Loud::move_assigned = 0;

TrackedObject::Result TrackedObject::current(0,0,0,0,0,0,0);
TrackedObject::Result TrackedObject::last(0,0,0,0,0,0,0);

}

#endif