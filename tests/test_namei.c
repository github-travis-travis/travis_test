#include "unity.h"
#include "unity_fixture.h"

#include "common.h"
#include "disk_emulator.h"
#include "inode_table.h"
#include "mkfs.h"
#include "namei.h"

TEST_GROUP_RUNNER(TestNameI) {
	RUN_TEST_CASE(TestNameI, test_iput_writes_to_root_directory_correctly);
}

TEST_GROUP(TestNameI);

// To be executed before each test case
TEST_SETUP(TestNameI) {
	init_disk_emulator();
	create_fs();
}

// To be executed after each test
TEST_TEAR_DOWN(TestNameI) {
	free_disk_emulator();
}

TEST(TestNameI, test_iput_writes_to_root_directory_correctly){
	struct inode root_inode;
	get_inode(ROOT_INODE_NUMBER, &root_inode);

	struct inode file_inode = {
		.inode_id = 500,
		.type = TYPE_ORDINARY,
		.links_nb = 1
	};
	put_inode(&file_inode);

	add_entry_to_parent(&root_inode, file_inode.inode_id, "test");
	put_inode(&root_inode);
 	
	TEST_ASSERT_EQUAL(file_inode.inode_id, namei("/test"));
}
