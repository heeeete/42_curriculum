#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private:
	int					value;
	const static int	bit = 8;
public:
	Fixed( void );
	Fixed (const int value);
	Fixed (const float value);
	Fixed(const Fixed& obj);
	~Fixed( void );
	Fixed&	operator=(const Fixed& obj);
	int		getRawBits( void ) const;
	void	setRawBits(int const raw);
	int		toInt( void ) const;
	float	toFloat( void ) const;
};

std::ostream& operator<<(std::ostream &temp, const Fixed& fixed);
#endif
