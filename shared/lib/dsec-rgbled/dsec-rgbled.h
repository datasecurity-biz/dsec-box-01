class DSecRGBLed {

	public:

		DSecRGBLed();

		uint8_t getR();
		uint8_t getG();
		uint8_t getB();

		void setR(uint8_t R);
		void setG(uint8_t G);
		void setB(uint8_t B);

		void setRGB( uint8_t R, uint8_t G, uint8_t B );
		void setRGB( uint8_t R, uint8_t G, uint8_t B, long rampTime );

		/**
		 * Convenience storage to keep implementation simpler - which number in
		 * a strip is this?  Eg: 4th LED in parent strip
		 */
		uint8_t getNumber();

		/**
		 * Convenience storage to keep implementation simpler - which number in
		 * a strip is this?  Eg: 4th LED in parent strip
		 */
		void setNumber(uint8_t number);


	private:

		uint8_t _number;

		int8_t _R;
		int8_t _G;
		int8_t _B;

		int8_t _targetR;
		int8_t _targetG;
		int8_t _targetB;

		long _targetMillis;

}
