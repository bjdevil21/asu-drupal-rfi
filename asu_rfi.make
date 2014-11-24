; ASU RFI makefile

api = 2
core = 7.x

; Upload multidev and patch it

projects[multiblock][version] = 7.x-1.1
projects[multiblock][subdir] = contrib
projects[multiblock][patch][] = https://www.drupal.org/files/issues/multiblock-cache-fix.patch
projects[multiblock][patch][] = https://www.drupal.org/files/fix_config_per_instance-1370966-5.patch

