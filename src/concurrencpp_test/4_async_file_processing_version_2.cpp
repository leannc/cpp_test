//
// Created by kang on 2024/7/25.
//
/*
        This example shows another version of processing a file asynchronously but this time
        we will use concurrencpp::resume_on to explicitly switch execution between executors.

        First we will reschedule the replace_chars_in_file task to run on the background executor in order to read
        the file. Then we will reschedule the task to run on the threadpool executor and replace the unwanted character.
        lastly we will reschedule the task to run again on the background executor in order to write the processed
        content back ot the file.

        The original version of this application does this rescheduling implicitly, by awaiting results that executor::submit
        produces. this version explicitly switches execution between executors and does not create sub-tasks from lambdas.
        Both versions are identical in terms of functionality and the final outcome.
*/

#include "UseCase.h"
concurrencpp::result<void> replace_chars_in_file_version_2(std::shared_ptr<concurrencpp::thread_pool_executor> background_executor,
                                                 std::shared_ptr<concurrencpp::thread_pool_executor> threadpool_executor,
                                                 const std::string file_path,
                                                 char from,
                                                 char to) {
    // switch control from whatever executor/thread this coroutine was called from to the background_executor.
    co_await concurrencpp::resume_on(background_executor);

    // we're running on the background executor now. we can safely block.
    std::vector<char> file_content;

    {
        std::ifstream input;
        input.exceptions(std::ifstream::badbit);
        input.open(file_path, std::ios::binary);
        file_content.assign(std::istreambuf_iterator<char>(input), {});
    }

    // switch execution to the threadpool-executor
    co_await concurrencpp::resume_on(threadpool_executor);

    // we're running on the threadpool executor now. we can process CPU-bound tasks now.
    for (auto& c : file_content) {
        if (c == from) {
            c = to;
        }
    }

    // switch execution back to the background-executor
    co_await concurrencpp::resume_on(background_executor);

    // write the processed file content. since we're running on the background executor, it's safe to block.
    std::ofstream output;
    output.exceptions(std::ofstream::badbit);
    output.open(file_path, std::ios::binary);
    output.write(file_content.data(), file_content.size());

    std::cout << "file has been modified successfully" << std::endl;
}

int async_file_processing_version_2() {

    const auto file_path = std::string("E:/Syncthing/tmp/test.txt");
    const auto from_char = 'k';
    const auto to_char = 's';

    concurrencpp::runtime runtime;

    try {
        replace_chars_in_file_version_2(runtime.background_executor(), runtime.thread_pool_executor(), file_path, from_char, to_char).get();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}