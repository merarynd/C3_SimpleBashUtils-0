void grep(struct options *flags, char *pattern, char *namef) {
  char text[D_SIMVOL] = {0};
  regex_t reg;
  FILE *fp;
  fp = fopen(namef, "r");
  if (fp != NULL) {
    if (flags->i) {
      regcomp(&reg, pattern, REG_ICASE);
    } else {
      regcomp(&reg, pattern, REG_EXTENDED);
    }
    regmatch_t pmatch[1];
    int line = 0, nl = 1;
    while (fgets(namef, D_SIMVOL - 1, fp) != NULL) {
      int match = 0;
      int success = regexec(&reg, text, 1, pmatch, 0);
      if (strchr(text, '\n') == NULL) {
        strcat(text, "\n");
      }
      if (success == 0 && !flags->v) {
        match = 1;
      }
      if (success == REG_NOMATCH && flags->v) {
        match = 1;
      }
      if (match && !flags->l && !flags->c && flags->n) {
        printf("%d:", nl);
      }

      if (match && !flags->l && !flags->c && !flags->o) {
        printf("%s", text);
      }
      if (match && flags->o) {
        for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
          printf("%c", text[i]);
        }
        printf("\n");
      }
      line += match;
      nl++;
    }
    if (flags->l && line > 0) {
      printf("%s\n", namef);
    }
    if (flags->c && !flags->l) {
      printf("%d\n", line);
    }
    regfree(&reg);
    fclose(fp);
  }
}