// #include <command/Parser.h>
//
// String5x7Buffer *parser::asciiParse(const string cmd, uint8_t screen_n) {
//   String5x7Buffer res;
//
//   string safeCmd = cmd + ';';
//   int left = 0;
//   for (int right = 1; right < safeCmd.length; ++right) {
//     if (safeCmd[right] == ';' && safeCmd[right-1] != '\\') {
//       if (left == 0) {
//         res = new String5x7Buffer(screen_n, safeCmd.substr(0, i-1));
//       } else {
//         parser::subProcess(res, safeCmd.substr(left, right-1))
//       }
//       left = right;
//     }
//   }
// }
//
// // cmd: one command sentence (not includes ';')
// void parser::subProcess(String5x7Buffer *string5x7Buffer, const string cmd) {
//   string trimmed_cmd
//   { // trim left/right spaces
//     size_t first = cmd.find_first_not_of(" ");
//     size_t last = cmd.find_last_not_of(" ");
//     trimmed_cmd = cmd.substr(first, last - first + 1);
//   }
//
//   if ("center" == trimmed_cmd) {
//     while (string5x7Buffer->distToCenter() > 0)
//       string5x7Buffer->leftScroll(false);
//   } else {
//     // pass
//   }
// }
