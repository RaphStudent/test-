//
//  CircularMotion.h
//  excalibur
//
//  Created by Kevin Kruusi on 2018-09-13.
//

#ifndef CircularMotion_h
#define CircularMotion_h

// constaint for pi
namespace physics {

	const double pi = 3.14159265359;

	// static class live coded for the circular motion lab
	class CircularMotion {
	public:

		/**
		converts degrees to radians.

		@param degrees #of
		@return # of radians
		*/
		static inline double degreesToRadians(const double degrees) {
			return (degrees * 2 * pi) / 360;
		};

		/**
		converts radians to revolutions

		@param radians #of
		@return # of revolutions
		*/
		static inline double radiansToRevolutions(const double radians) {
			return (radians * 1) / (2 * pi);
		};

		/**
		converts revolutions to degrees

		@param revolutions value arguement
		@return corresponding degrees
		*/
		static inline double revolutionsToDegrees(const double revolutions) {
			return revolutions * 360;
		};

		/**
		converts revolutions per minute to revolutions per second

		@param revsPerMinute revs/minute argument
		@return revolutions per second or rev/s
		*/
		static inline double rpmToRps(const double revsPerMinute) {
			return revsPerMinute / 60;
		};

		/**
		converts revolutions per minute to rads per second

		@param revsPerMinute revolutions/minute argument
		@return result in radians/second
		*/
		static inline double radsPerSecondFromRevsPerMinute(const double revsPerMinute) {
			double revsPerSecond = CircularMotion::rpmToRps(revsPerMinute);;
			double degrees = CircularMotion::revolutionsToDegrees(revsPerSecond);
			return CircularMotion::degreesToRadians(degrees);
		};
	};
};
#endif /* CircularMotion_h */