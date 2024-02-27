/*
 * Queue.h
 *
 *  Created on: Feb 27, 2024
 *      Author: jay94
 */

#ifndef APP_QUEUE_H_
#define APP_QUEUE_H_

#include <stdint.h>

template<typename T, int size>
class Queue {
private:
	uint16_t _rp, _wp;
	uint16_t _len;
	volatile T _buf[size];

public:
	Queue() : _rp(0), _wp(0), _len(0) { }

public:
	uint16_t capacity() const { return sizeof(_buf); }
	uint16_t used() const { return _len; }
	uint16_t avail() const { return sizeof(_buf) - _len; }

	/* erase all elements and reset the queue. */
	void clear() {
		_len = _rp = _wp = 0;
	}

	/* enqueue an element. */
	bool enqueue(const T& buf) {
		if (_len < sizeof(_buf)) {
			_buf[_wp++] = buf;
			_len++;

			if (_wp >= sizeof(_buf)) {
				_wp = 0;
			}

			return true;
		}

		return false;
	}

	/* enqueue elements. */
	uint16_t enqueue(const T* buf, uint16_t len) {
		uint16_t ret = 0;

		while (len) {
			if(!enqueue(*buf)) {
				break;
			}

			len--;
			buf++;
			ret++;
		}

		return ret;
	}

	/* dequeue an element. */
	bool dequeue(T& buf) {
		if (_len > 0) {
			buf = _buf[_rp++];
			_len--;

			if (_rp >= sizeof(_buf)) {
				_rp = 0;
			}

			return true;
		}

		return false;
	}

	/* dequeue elements. */
	uint16_t dequeue(T* buf, uint16_t len) {
		uint16_t ret = 0;

		while (len) {
			if (!dequeue(*buf)) {
				break;
			}

			len--;
			buf++;
			ret++;
		}

		return ret;
	}

	/* peek an element. */
	bool peek(uint16_t offset, T& buf) {
		if (_len > offset) {
			uint8_t rp = _rp + offset;
			while (rp >= sizeof(_buf)) {
				rp -= sizeof(_buf);
			}

			buf = _buf[rp];
			return true;
		}

		return false;
	}

	/* peek elements */
	uint16_t peek(uint16_t offset, T* buf, uint16_t len) {
		uint16_t ret = 0;

		while(len) {
			if (!peek(offset + ret, *buf)) {
				break;
			}

			len--;
			buf++;
			ret++;
		}

		return ret;
	}
};



#endif /* APP_QUEUE_H_ */
