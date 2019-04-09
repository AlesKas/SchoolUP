using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using HW8.Models;

namespace HW8.Controllers
{
    public class StudentSubjectsController : BaseController
    {
        Student temp;
        public ActionResult All()
        {
            List <Student> st = Ctx.Students.ToList();
            ViewBag.Blekeke = "tralala";
            return View(st);
        }

        [HttpGet]
        public ActionResult SelectStudent()
        {
            List<Student> st = Ctx.Students.ToList();
            return View(st);
        }

        public ActionResult SelectSubject()
        {
            List<Subject> sub = Ctx.Subjects.ToList();
            return View(sub);
        }


        [HttpPost]
        public ActionResult SelectStudent(int id)
        {
            Student stud = Ctx.Students.FirstOrDefault(p => p.Id == id);
            if (stud != null)
            {
                temp = stud;
                return RedirectToAction("SelectSubject");
            }
             else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }

        [HttpPost]
        public ActionResult SelectSubject(int id)
        {
            Subject subj = Ctx.Subjects.FirstOrDefault(p => p.Id == id);
            if (subj != null)
            {
                temp.Subjects.Add(subj);
                Ctx.SaveChanges();
                return RedirectToAction("All");
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }

    }
}