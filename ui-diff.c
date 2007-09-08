	subproject = (S_ISGITLINK(mode1) || S_ISGITLINK(mode2));
	if (S_ISGITLINK(pair->one->mode) || S_ISGITLINK(pair->two->mode)) {
		if (S_ISGITLINK(pair->one->mode))
		if (S_ISGITLINK(pair->two->mode))
void cgit_print_diff(const char *new_rev, const char *old_rev)
	struct commit *commit, *commit2;

	if (!new_rev)
		new_rev = cgit_query_head;
	get_sha1(new_rev, sha1);
	type = sha1_object_info(sha1, &size);
	if (type == OBJ_BAD) {
		cgit_print_error(fmt("Bad object name: %s", new_rev));
		return;
	}
	if (type != OBJ_COMMIT) {
		cgit_print_error(fmt("Unhandled object type: %s",
				     typename(type)));
	commit = lookup_commit_reference(sha1);
	if (!commit || parse_commit(commit))
		cgit_print_error(fmt("Bad commit: %s", sha1_to_hex(sha1)));
	if (old_rev)
		get_sha1(old_rev, sha2);
	else if (commit->parents && commit->parents->item)
		hashcpy(sha2, commit->parents->item->object.sha1);
	else
		hashclr(sha2);

	if (!is_null_sha1(sha2)) {
			cgit_print_error(fmt("Bad object name: %s", sha1_to_hex(sha2)));
		commit2 = lookup_commit_reference(sha2);
		if (!commit2 || parse_commit(commit2))
			cgit_print_error(fmt("Bad commit: %s", sha1_to_hex(sha2)));
	html("<tr><td>");
	cgit_diff_tree(sha2, sha1, filepair_cb);
	html("</td></tr>");