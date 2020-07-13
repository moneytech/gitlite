#include <stdio.h>
#include <stdlib.h>

#include <git2/global.h>
#include <git2/clone.h>
#include <git2/errors.h>

// Compile with:
// clang90 -o gitlite gitlite.c -lgit2 -I/usr/local/include -L/usr/local/lib -g

void
git_bail_error(int rc)
{
    const git_error *err = NULL;

	if (rc < 0) {
		err = git_error_last();
		if (err) 
            printf("ERROR %d: %s\n", err->klass, err->message);
		else 
            printf("ERROR %d: cannot fetch error info\n", rc);

    }
}

int
main(int argc, char *argv[])
{
	int rc;
	const char *url = "https://github.com/freebsd/pkg.git";
	//const char *url = "https://github.com/freebsd/freebsd.git";
	const char *local_path = "/home/sbz/git/src";
	git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
	git_checkout_options co_opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_repository *cloned_repo = NULL;

	co_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	co_opts.progress_cb = NULL;
	co_opts.progress_payload = NULL;
	clone_opts.checkout_opts = co_opts;
	clone_opts.fetch_opts.callbacks.sideband_progress = NULL;
	clone_opts.fetch_opts.callbacks.transfer_progress = NULL;
	clone_opts.fetch_opts.callbacks.credentials = NULL;
	clone_opts.fetch_opts.callbacks.payload = NULL;

	rc = git_libgit2_init();
	git_bail_error(rc);

	rc = git_clone(&cloned_repo, url, local_path, &clone_opts);
	git_bail_error(rc);

	if (cloned_repo)
		git_repository_free(cloned_repo);

	rc = git_libgit2_shutdown();
	git_bail_error(rc);

    return (rc);
}
