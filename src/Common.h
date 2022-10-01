#ifndef _COMMON_H_
#define _COMMON_H_

/**
 * @brief valを [low, high] に収める
 * 
 */
#define MACR_CLIP(val, low, high) { \
  if ((val) < (low)) { \
    (val) = (low); \
  } else if ((high) < (val)) { \
    (val) = (high); \
  } \
}

#endif  /* _COMMON_H_ */