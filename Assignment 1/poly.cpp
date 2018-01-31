	// poly.cpp

#include "poly.h"
#include<cmath>
#include<iostream>

	// GCD function finds the Greatest Common Denominator recursively

int GCD(int a, int b) {

	if (b == 0)
		return a;
	else
		return GCD(b, a%b);
}

	// divide operator returns the quotient calculated after diving 2 polynomials
	// it is a wrapper function for the actual recursive divide function  

Polynomial operator/(const Polynomial& p1, const Polynomial& p2) {
	
	Polynomial quotient;
	Polynomial remainder;

	divide(p1, p2, quotient, remainder);

	return quotient;
}

	// modulus operator returns the remainder obtained after divind 2 polynomials
	// it is a wrapper function which calls the recursive divide function

Polynomial operator%(const Polynomial& p1, const Polynomial& p2) {
	
	Polynomial quotient;
	Polynomial remainder;

	divide(p1, p2, quotient, remainder);

	return remainder;
}

	// divide is a recursive function which is used to divide 2 polynomials
	// it keep calling itself until the highest exponent of divisor is less than or equal to highest exponent of divident
	// it calculates and save quotient and remainder for / and % operator functions
	// at the initial call of divide() from above functions, quotient and remainder are not defined

void divide(const Polynomial& p1, const Polynomial& p2,Polynomial& quotient, Polynomial& remainder) {

	// iterators to transverse through polynomials

	auto it1 = p1.poly_.begin();
	auto it2 = p2.poly_.begin();

	// base case for recursive function which ends the recursion only when condition satisfied
	// STEP 1

	if ((*it2).exponent_ > (*it1).exponent_) {
		Fraction f(0, 1);
		quotient.addTerm(f, 0);
		remainder = p1;
	}
	else {
	
	// temporary variables of Polynomial type to save new values calculated while dividing

		Polynomial temp;
		Polynomial quo;
		Polynomial newp1 = p1;

	// calculating the term of quotient
	// STEP 2

		Fraction coeff = (*it1).coefficient_ / (*it2).coefficient_;
		unsigned int expo = (*it1).exponent_ - (*it2).exponent_;
		quo.addTerm(coeff, expo);

	// saving the term into quotient polynomial

		quotient += quo;

	// creating a tempory term as a product of divisor and quotient term
	// STEP 3

		temp = p2*quo;

	// creating a new p1 polynomial to pass it in recursive call of divide function
	// STEP 4

		newp1 -= temp;

	// calling divide as recursive
	// STEP 5

		divide(newp1, p2, quotient, remainder);
	}
}


int abs(int v) {
	return (v >= 0) ? v : -v;
}

Fraction::Fraction() {
	numerator_ = 0;
	denominator_ = 1;
}
Fraction::Fraction(int num, int denom) {
	set(num, denom);
}
void Fraction::set(int num, int denom) {
	numerator_ = num;
	denominator_ = denom;
	reduce();
}
void Fraction::reduce() {
	int divisor = GCD(numerator_, denominator_);
	numerator_ = numerator_ / divisor;
	denominator_ = denominator_ / divisor;
	//always store negative in numerator
	if ((numerator_ < 0 && denominator_ < 0) ||
		(numerator_ > 0 && denominator_ < 0)) {
		numerator_ = numerator_*-1;
		denominator_ = denominator_*-1;
	}
}
bool isSame(const Term& a, const Term& b)
{
	bool rc = false;
	if (a.coefficient_ == b.coefficient_ && a.exponent_
		== b.exponent_) {
		rc = true;
	}
	return rc;
}
Fraction operator+(const Fraction& f1, const Fraction& f2) {
	return Fraction(f1.numerator_*f2.denominator_ +
		f2.numerator_*f1.denominator_,
		f1.denominator_*f2.denominator_);

}
Fraction operator-(const Fraction& f1, const Fraction& f2) {
	return Fraction(f1.numerator_*f2.denominator_ -
		f2.numerator_*f1.denominator_,
		f1.denominator_*f2.denominator_);

}
Fraction operator*(const Fraction& f1, const Fraction& f2) {
	return Fraction(f1.numerator_*f2.numerator_,
		f1.denominator_*f2.denominator_);
}
Fraction operator/(const Fraction& f1, const Fraction& f2) {
	return Fraction(f1.numerator_*f2.denominator_,
		f1.denominator_*f2.numerator_);
}
ostream& operator << (ostream& os, const Fraction& data) {
	if (abs(data.numerator_) < abs(data.denominator_)) {
		if (data.numerator_ != 0) {
			os << data.numerator_ << "/" <<
				data.denominator_;
		}
		else {
			os << "0";
		}
	}
	else {
		os << data.numerator_ / data.denominator_;
		if (data.numerator_ % data.denominator_) {
			os << " " <<
				
abs(data.numerator_%data.denominator_) << "/";
			os << data.denominator_;
		}
	}
	return os;
}

const Fraction& Fraction::operator+=(const Fraction& rhs) {
	*this = *this + rhs;
	return *this;
}
const Fraction& Fraction::operator-=(const Fraction& rhs) {
	*this = *this - rhs;
	return *this;
}
const Fraction& Fraction::operator*=(const Fraction& rhs) {
	*this = *this * rhs;
	return *this;
}
const Fraction& Fraction::operator/=(const Fraction& rhs) {
	*this = *this / rhs;
	return *this;
}
bool operator==(const Fraction& f1, const Fraction& f2) {
	bool rc = true;
	if ((f1.numerator_ != f2.numerator_) ||
		(f1.denominator_ != f2.denominator_)) {
		rc = false;
	}
	return rc;
}
bool operator!=(const Fraction& f1, const Fraction& f2) {
	bool rc = true;
	if ((f1.numerator_ == f2.numerator_) &&
		(f1.denominator_ == f2.denominator_)) {
		rc = false;
	}
	return rc;
}
Polynomial::Polynomial(int data[][3], int numTerms) {
	for (int i = 0; i<numTerms; i++) {
		poly_.insert(Term(data[i][0], data[i][1],
			data[i][2]));
	}
}
Polynomial::Polynomial(const Polynomial& poly) {
	poly_ = poly.poly_;
}
const Polynomial& Polynomial::operator=(const Polynomial&
	poly) {
	poly_ = poly.poly_;
	return *this;
}
void Polynomial::clear() {
	poly_.erase(poly_.begin(), poly_.end());
}
Polynomial::~Polynomial() {
}
void Polynomial::addTerm(const Fraction& coefficient, int
	degree) {
	Term t(coefficient, degree);
	//search for a term with the same exponent
	auto it = poly_.search(t);
	if (it == poly_.end()) {
		poly_.insert(t);
	}
	else {
		(*it).coefficient_ += coefficient;
	}

}

	// BONUS
	// updated and efficient solve function

Fraction Polynomial::solve(const Fraction& x) const {

	Fraction rc;
        
	auto it=poly_.begin();
        
	while(it!=poly_.end()){
                Term t=*it;

                Fraction x_=x;

	// using math function pow to calculate numerator and denominator

                double n=pow((double)x_.numerator(),(double)t.exponent_);
                double d=pow((double)x_.denominator(),(double)t.exponent_);

	// calculating current fraction using above values instead of a loop

                Fraction curr((int)n,(int)d);

                curr.reduce();

                rc+=t.coefficient_*curr;
                it++;
        }
        return rc;

}
const Polynomial& Polynomial::operator+=(const Polynomial&
	rhs) {
	auto it1 = poly_.begin();
	auto it2 = rhs.poly_.begin();
	while (it1 != poly_.end() && it2 != rhs.poly_.end())
	{
		if (*it1 == *it2) {
			(*it1).coefficient_ +=
				(*it2).coefficient_;
			if ((*it1).coefficient_ ==
				Fraction(0, 1)) {
				it1 = poly_.erase(it1);
			}
			else {
				it1++;
			}
			it2++;
		}
		else if (*it1 < *it2) {
			it1++;
		}
		else {
			addTerm((*it2).coefficient_,
				(*it2).exponent_);
			it2++;
		}
	}
	while (it2 != rhs.poly_.end()) {
		addTerm((*it2).coefficient_,
			(*it2).exponent_);
		it2++;
	}

	return *this;
}
const Polynomial& Polynomial::operator-=(const Polynomial&
	rhs) {
	auto it1 = poly_.begin();
	auto it2 = rhs.poly_.begin();
	while (it1 != poly_.end() && it2 != rhs.poly_.end())
	{
		if (*it1 == *it2) {
			(*it1).coefficient_ -=
				(*it2).coefficient_;
			if ((*it1).coefficient_ ==
				Fraction(0, 1)) {
				it1 = poly_.erase(it1);
			}
			else {
				it1++;
			}
			it2++;
		}
		else if (*it1 < *it2) {
			it1++;
		}
		else {
			addTerm(Fraction(-1, 1)*
				(*it2).coefficient_, 
(*it2).exponent_);
			it2++;
		}
	}
	while (it2 != rhs.poly_.end()) {
		addTerm(Fraction(-1, 1)*(*it2).coefficient_,
			(*it2).exponent_);
		it2++;
	}
	return *this;

}
const Polynomial& Polynomial::operator*=(const Polynomial&
	rhs) {
	auto it2 = rhs.poly_.begin();
	Polynomial temp;
	while (it2 != rhs.poly_.end()) {
		auto it1 = poly_.begin();
		while (it1 != poly_.end()) {

			
temp.addTerm((*it1).coefficient_*(*it2).coefficient_,
				(*it1).exponent_ + 
(*it2).exponent_);
			it1++;
		}
		it2++;
	}
	*this = temp;
	return *this;
}



Polynomial operator+(const Polynomial& p1, const Polynomial&
	p2) {
	Polynomial rc = p1;
	rc += p2;
	return rc;
}
Polynomial operator-(const Polynomial& p1, const Polynomial&
	p2) {
	Polynomial rc = p1;
	rc -= p2;
	return rc;
}
Polynomial operator*(const Polynomial& p1, const Polynomial&
	p2) {
	Polynomial rc = p1;
	rc *= p2;
	return rc;
}

bool operator==(const Polynomial& p1, const Polynomial& p2) {
	auto it1 = p1.poly_.begin();
	auto it2 = p2.poly_.begin();
	bool rc = true;
	while (rc && it1 != p1.poly_.end() && it2 !=
		p2.poly_.end()) {
		if (!isSame(*it1, *it2)) {
			rc = false;
		}
		it1++;
		it2++;
	}
	if (rc) {
		return (it1 == p1.poly_.end() && it2 ==
			p2.poly_.end());
	}
	else {
		return rc;
	}
}
ostream& operator<<(ostream& os, const Polynomial& dat) {
	auto it = dat.poly_.begin();
	if (it != dat.poly_.end()) {
		os << (*it).coefficient_ << " x^" <<
			(*it).exponent_;
		it++;
		while (it != dat.poly_.end()) {
			os << " + ";
			os << (*it).coefficient_;
			if ((*it).exponent_ > 1) {
				os << " x^" <<
					(*it).exponent_;
			}
			else if ((*it).exponent_ == 1) {
				os << " x";
			}
			it++;
		}
	}
	else {
		os << "0" << endl;
	}
	return os;
}

