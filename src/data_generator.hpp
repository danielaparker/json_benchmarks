#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

const uint64_t escape_sequence = 1;

void make_big_file(const char *filename, size_t count, size_t numIntegers, size_t numDoubles, uint64_t flags);

#endif
