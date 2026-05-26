#include <gtest/gtest.h>
#include <thread>
#include <atomic>
#include <string>
#include <vector>
#include <chrono>
#include "thread_safe_queue.hpp"

namespace rp_test
{
    // --- Single Thread Tests ---

    TEST(ThreadSafeQueueTest, BasicEmptyCheck)
    {
        rp::ThreadSafeQueue<int> tsq;

        EXPECT_TRUE(tsq.empty());
        EXPECT_EQ(tsq.size(), 0);
    }

    TEST(ThreadSafeQueueTest, TryGetDataEmptyReturnsFalse)
    {
        rp::ThreadSafeQueue<int> tsq;
        int data = -1;

        EXPECT_FALSE(tsq.try_getData(data));
        EXPECT_EQ(data, -1);
    }

    TEST(ThreadSafeQueueTest, AddAndTryGetDataSuccess)
    {
        rp::ThreadSafeQueue<std::string> tsq;
        tsq.addData("message 1");
        tsq.addData("message 2");

        EXPECT_FALSE(tsq.empty());
        EXPECT_EQ(tsq.size(), 2);

        std::string data;
        EXPECT_TRUE(tsq.try_getData(data));
        EXPECT_EQ(data, "message 1");

        EXPECT_TRUE(tsq.try_getData(data));
        EXPECT_EQ(data, "message 2");

        EXPECT_TRUE(tsq.empty());
        EXPECT_EQ(tsq.size(), 0);
    }

    // --- Concurrency And Blocking Tests ---

    TEST(ThreadSafeQueueTest, WaitGetDataUnblocksOnData)
    {
        rp::ThreadSafeQueue<int> tsq;
        int data{0};
        std::atomic<bool> finished{false};

        {
            std::jthread consumer([&]{
                EXPECT_TRUE(tsq.wait_getData(data));
                finished = true;
            });

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            EXPECT_FALSE(finished);

            tsq.addData(20);
        }

        EXPECT_TRUE(finished);
        EXPECT_EQ(data, 20);
    }

    TEST(ThreadSafeQueueTest, WaitGetDataUnblocksOnDone)
    {
        rp::ThreadSafeQueue<int> tsq;
        int data{0};
        std::atomic<bool> finished{false};

        {
            std::jthread consumer([&]{
                EXPECT_FALSE(tsq.wait_getData(data));
                finished = true;
            });

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            EXPECT_FALSE(finished);

            tsq.done();
        }

        EXPECT_TRUE(finished);
        EXPECT_EQ(data, 0);
    }

    // --- Multi Thread Stress Test ---

    TEST(ThreadSafeQueueTest, MultipleProducersAndConsumers)
    {
        rp::ThreadSafeQueue<int> tsq;
        const int producer_count = 3;
        const int consumer_count = 3;
        const int items_per_producer = 1000;
        std::atomic<int> total_consumed{0};

        auto producer_task = [&tsq, &items_per_producer]{
            for(int i=0; i < items_per_producer; i++)
            {
                tsq.addData(1);
            }
        };

        auto consumer_task = [&tsq, &total_consumed]{
            int data{0};
            while(tsq.wait_getData(data))
            {
                total_consumed+=data;
            }
        };

        std::vector<std::jthread> consumers;
        for(int i=0; i < consumer_count; i++)
        {
            consumers.emplace_back(consumer_task);
        }

        {
            std::vector<std::jthread> producers;
            for(int i=0; i < producer_count; i++)
            {
                producers.emplace_back(producer_task);
            }
        }

        tsq.done();
        consumers.clear();

        EXPECT_TRUE(tsq.empty());
        EXPECT_EQ(tsq.size(), 0);
        EXPECT_EQ(total_consumed.load(), producer_count * items_per_producer);
    }
}
